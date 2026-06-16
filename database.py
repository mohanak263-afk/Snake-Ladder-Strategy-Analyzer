import sqlite3


def init_db():

    conn = sqlite3.connect("leaderboard.db")

    cursor = conn.cursor()

    cursor.execute("""
    CREATE TABLE IF NOT EXISTS leaderboard
    (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        player TEXT UNIQUE,
        wins INTEGER DEFAULT 0
    )
    """)

    conn.commit()
    conn.close()


def add_win(player):

    conn = sqlite3.connect("leaderboard.db")

    cursor = conn.cursor()

    cursor.execute(
        """
        INSERT OR IGNORE INTO leaderboard
        (player,wins)
        VALUES (?,0)
        """,
        (player,)
    )

    cursor.execute(
        """
        UPDATE leaderboard
        SET wins = wins + 1
        WHERE player = ?
        """,
        (player,)
    )

    conn.commit()
    conn.close()


def get_leaderboard():

    conn = sqlite3.connect("leaderboard.db")

    cursor = conn.cursor()

    cursor.execute(
        """
        SELECT player,wins
        FROM leaderboard
        ORDER BY wins DESC
        """
    )

    rows = cursor.fetchall()

    conn.close()

    return rows