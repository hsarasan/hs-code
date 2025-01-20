const express = require('express');
const path = require('path');
const { Pool } = require('pg');
const passport = require('passport');
const GoogleStrategy = require('passport-google-oauth20').Strategy;
const session = require('express-session');
require('dotenv').config();

const app = express();
const pool = new Pool({
  user: process.env.DB_USER,
  host: 'localhost',
  database: process.env.DB_NAME,
  password: process.env.DB_PASSWORD,
  port: 5432,
});

// Middleware to parse JSON request bodies
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
  const googleId = profile.id; // Extract Google ID from the profile
  const user = { google_id: googleId, displayName: profile.displayName }; // Customize as needed
  return done(null, user); // Pass user object to serializeUser
}));

// Passport session middleware
app.use(passport.initialize());
app.use(passport.session());

// Routes
app.get('/', (req, res) => {
  if (req.isAuthenticated()) {
    res.redirect('/landing');
  } else {
    res.sendFile(path.join(__dirname, 'public', 'index.html')); // Show login page if not authenticated
  }
});

// Google login route
app.get('/auth/google', passport.authenticate('google', { scope: ['profile'] }));

// Google callback route
app.get('/auth/google/callback', passport.authenticate('google', { failureRedirect: '/' }), (req, res) => {
  res.redirect('/landing'); // Redirect to the landing page after successful login
});

// Logout route
app.get('/logout', (req, res) => {
  req.logout((err) => {
    res.redirect('/');
  });
});

// Landing Page route
app.get('/landing', (req, res) => {
  if (req.isAuthenticated()) {
    res.sendFile(path.join(__dirname, 'public', 'landing.html'));
  } else {
    res.redirect('/');
  }
});

// Create Flashcard Page
app.get('/create-page', (req, res) => {
  if (req.isAuthenticated()) {
    res.sendFile(path.join(__dirname, 'public', 'create.html'));
  } else {
    res.redirect('/');
  }
});

// Retrieve Flashcard Page
app.get('/retrieve-page', (req, res) => {
  if (req.isAuthenticated()) {
    res.sendFile(path.join(__dirname, 'public', 'retrieve.html'));
  } else {
    res.redirect('/');
  }
});

// POST endpoint to create a new flashcard
app.post('/flashcards', (req, res) => {
  const { question, answer } = req.body;

  if (!req.isAuthenticated() || !req.user) {
    return res.status(401).json({ error: 'Unauthorized: User not authenticated' });
  }

  const googleId = req.user.google_id; // Extract google_id from session

  if (!question || !answer) {
    return res.status(400).json({ error: 'Question and answer are required' });
  }

  pool.query(
    'INSERT INTO flashcards (google_id, question, answer) VALUES ($1, $2, $3) RETURNING *',
    [googleId, question, answer],
    (err, result) => {
      if (err) {
        console.error('Error inserting flashcard', err.stack);
        return res.status(500).json({ error: 'Failed to create flashcard' });
      }
      res.status(201).json(result.rows[0]); 
    }
  );
});

// GET endpoint to retrieve all flashcards for the logged-in user
app.get('/flashcards', (req, res) => {
  if (!req.isAuthenticated() || !req.user) {
    return res.status(401).json({ error: 'Unauthorized: User not authenticated' });
  }

  const googleId = req.user.google_id; // Get user's google_id

  pool.query(
    'SELECT * FROM flashcards WHERE google_id = $1',
    [googleId],
    (err, result) => {
      if (err) {
        console.error('Error retrieving flashcards', err.stack);
        return res.status(500).json({ error: 'Failed to retrieve flashcards' });
      }
      res.status(200).json(result.rows); // Return only the user's flashcards
    }
  );
});

// Start the server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});
