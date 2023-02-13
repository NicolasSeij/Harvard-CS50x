import cs50

db = cs50.SQL("sqlite:///songs.db")

rows = db.execute("SELECT tempo, name FROM songs ORDER BY tempo DESC")

for row in rows:
    print(row)