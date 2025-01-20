const express = require('express');
const path = require('path');
const { Pool } = require('pg');
const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20').Strategy;
const session = require('express-session');
require('dotenv').config();


const app = express();

// Setup EJS view engine
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views')); 

const pool = new Pool({
  user: process.env.DB_USER,
  host: 'localhost',
  database: process.env.DB_NAME,
  password: process.env.DB_PASSWORD,
  port: 5432,
});

// Middleware to parse JSON request bodies
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

// Session middleware
app.use(session({
  secret: 'your-secret-key',
  resave: false,
  saveUninitialized: true,
}));

// Passport setup
passport.serializeUser((user, done) => {
  done(null, user);
});

passport.deserializeUser((user, done) => {
  done(null, user);
});

// Google OAuth strategy
passport.use(new GoogleStrategy({
  clientID: process.env.GOOGLE_CLIENT_ID,
  clientSecret: process.env.GOOGLE_CLIENT_SECRET,
  callbackURL: 'http://localhost:3000/auth/google/callback',
}, (accessToken, refreshToken, profile, done) => {
  const googleId = profile.id; // Extract the Google ID from the profile
  const user = { google_id: googleId, displayName: profile.displayName };
  return done(null, user); // Pass user data to serializeUser
}));

// Passport session middleware
app.use(passport.initialize());
app.use(passport.session());

// Routes
app.get('/', (req, res) => {
  if (req.isAuthenticated()) {
    res.redirect('/landing');
  } else {
    res.sendFile(path.join(__dirname, 'public', 'index.html')); // Serve login page if not authenticated
  }
});

// Google login route
app.get('/auth/google', (req, res, next) => {
  console.log('Google auth route hit'); // Debugging log
  next();
}, passport.authenticate('google', { scope: ['profile', 'email'] }));

// Google callback route
app.get('/auth/google/callback', passport.authenticate('google', { failureRedirect: '/' }), (req, res) => {
  console.log('Google authentication successful'); // Debugging log
  res.redirect('/landing'); // Redirect to landing page after successful login
});

// Logout route
app.get('/logout', (req, res) => {
  req.logout((err) => {
    if (err) {
      console.error('Error during logout:', err);
      return res.status(500).json({ error: 'Failed to log out' });
    }
    res.redirect('/');
  });
});

// Landing page route
app.get('/landing', (req, res) => {
  if (req.isAuthenticated()) {
    res.sendFile(path.join(__dirname, 'public', 'landing.html'));
  } else {
    res.redirect('/');
  }
});

// Route to serve create page (for creating a new flashcard)
app.get('/create-page', (req, res) => {
  if (req.isAuthenticated()) {
    res.sendFile(path.join(__dirname, 'public', 'create-page.html'));  // Make sure 'create-page.html' exists in 'public' folder
  } else {
    res.redirect('/'); // Redirect to login if not authenticated
  }
});


// POST endpoint to create a new flashcard
app.post('/flashcards', (req, res) => {
  const { subject, topic, question, answer } = req.body;

  if (!req.isAuthenticated() || !req.user) {
    return res.status(401).json({ error: 'Unauthorized: User not authenticated' });
  }

  const googleId = req.user.google_id;

  if (!subject || !topic || !question || !answer) {
    return res.status(400).json({ error: 'Subject, topic, question, and answer are required' });
  }

  pool.query(
    'INSERT INTO flashcards (google_id, subject, topic, question, answer) VALUES ($1, $2, $3, $4, $5) RETURNING *',
    [googleId, subject, topic, question, answer],
    (err, result) => {
      if (err) {
        console.error('Error inserting flashcard:', err.stack);
        return res.status(500).json({ error: 'Failed to create flashcard' });
      }
      res.status(201).json(result.rows[0]);
    }
  );
});

app.get('/retrieve-page', (req, res) => {
  if (!req.isAuthenticated() || !req.user) {
    return res.status(401).json({ error: 'Unauthorized: User not authenticated' });
  }

  const googleId = req.user.google_id;

  // Query to get distinct subjects for the logged-in user
  pool.query(
    'SELECT DISTINCT subject FROM flashcards WHERE google_id = $1',
    [googleId],
    (err, result) => {
      if (err) {
        console.error('Error retrieving subjects:', err.stack);
        return res.status(500).json({ error: 'Failed to retrieve subjects' });
      }

      // Render the retrieve-form.ejs view and pass subjects to it
      res.render('retrieve-form', {
        subjects: result.rows.map(row => row.subject),
      });
    }
  );
});

app.get('/retrieve-topics', (req, res) => {
  const { subject } = req.query;

  if (!subject) {
    return res.status(400).json({ error: 'Subject is required' });
  }

  const googleId = req.user.google_id;

  // Query to get distinct topics for the selected subject and user
  pool.query(
    'SELECT DISTINCT topic FROM flashcards WHERE google_id = $1 AND subject = $2',
    [googleId, subject],
    (err, result) => {
      if (err) {
        console.error('Error retrieving topics:', err.stack);
        return res.status(500).json({ error: 'Failed to retrieve topics' });
      }

      // Send the topics back as JSON
      res.json({ topics: result.rows.map(row => row.topic) });
    }
  );
});

app.post('/get-topics', (req, res) => {
  const { subject } = req.body;
  const googleId = req.user.google_id; // Assuming user is logged in

  // Query to get topics for the specific subject and user
  pool.query(
    'SELECT DISTINCT topic FROM flashcards WHERE google_id = $1 AND subject = $2',
    [googleId, subject],
    (err, result) => {
      if (err) {
        console.error('Error retrieving topics:', err.stack);
        return res.status(500).json({ error: 'Failed to retrieve topics' });
      }

      // Send the topics as a JSON response
      res.json(result.rows);
    }
  );
});


app.post('/retrieve-flashcards', (req, res) => {
  const { subject, topic } = req.body;
  console.log('subject & topic', subject, topic);

  if (!subject || !topic) {
    return res.status(400).json({ error: 'Subject and topic are required' });
  }

  const googleId = req.user.google_id;

  // Query to retrieve flashcards for the selected subject and topic
  pool.query(
    'SELECT * FROM flashcards WHERE google_id = $1 AND subject = $2 AND topic = $3',
    [googleId, subject, topic],
    (err, result) => {
      if (err) {
        console.error('Error retrieving flashcards:', err.stack);
        return res.status(500).json({ error: 'Failed to retrieve flashcards' });
      }

      // Render the flashcards page and pass the flashcards to it
      res.render('flashcards', {
        flashcards: result.rows,
        subject: subject,
        topic: topic,
        currentFlashcardIndex: 0 // Set the starting flashcard index
      });
    }
  );
});

// Start the server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});

