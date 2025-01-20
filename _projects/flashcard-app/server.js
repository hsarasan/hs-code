const express = require('express');
const path = require('path');  // Import the path module
const { Pool } = require('pg');
const passport = require('passport');
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
app.use(express.json());  // Handle JSON bodies

// Serve static files (like HTML, CSS, JS)
app.use(express.static(path.join(__dirname, 'public')));

// POST endpoint to create a new flashcard
app.post('/flashcards', (req, res) => {
  const { question, answer } = req.body;

  if (!question || !answer) {
    return res.status(400).json({ error: 'Question and answer are required' });
  }

  pool.query(
    'INSERT INTO flashcards (question, answer) VALUES ($1, $2) RETURNING *',
    [question, answer],
    (err, result) => {
      if (err) {
        console.error('Error inserting flashcard', err.stack);
        return res.status(500).json({ error: 'Failed to create flashcard' });
      }
      res.status(201).json(result.rows[0]);  // Return the newly created flashcard
    }
  );
});

// GET endpoint to retrieve all flashcards
app.get('/flashcards', (req, res) => {
  pool.query('SELECT * FROM flashcards', (err, result) => {
    if (err) {
      console.error('Error retrieving flashcards', err.stack);
      return res.status(500).json({ error: 'Failed to retrieve flashcards' });
    }
    res.status(200).json(result.rows);  // Return all flashcards
  });
});

// Default route to serve the HTML file
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));  // Serve the index.html
});

// Start the server
app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
});
