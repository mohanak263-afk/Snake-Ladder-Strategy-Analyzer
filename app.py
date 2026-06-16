from flask import Flask, render_template, jsonify, session
import subprocess

from database import (
    init_db,
    add_win,
    get_leaderboard
)

app = Flask(__name__)
app.secret_key = "snake_ladder_secret"

init_db()


@app.route("/")
def home():
    return render_template("home.html")


@app.route("/game")
def game():

    if "player1" not in session:
        session["player1"] = 1

    if "player2" not in session:
        session["player2"] = 1

    if "current_player" not in session:
        session["current_player"] = 1

    if "winner" not in session:
        session["winner"] = 0

    bfs_result = subprocess.run(
        ["c_backend/snake_backend.exe", "bfs"],
        capture_output=True,
        text=True
    )

    bfs_data = bfs_result.stdout.strip().split("|",1)

    bfs_moves = bfs_data[0]

    if len(bfs_data) > 1:
        bfs_path = bfs_data[1]
    else:
        bfs_path = "Path unavailable"

    return render_template(
        "game.html",
        player1=session["player1"],
        player2=session["player2"],
        current_player=session["current_player"],
        bfs_moves=bfs_moves,
        bfs_path=bfs_path
    )


@app.route("/leaderboard")
def leaderboard():

    rows = get_leaderboard()

    return render_template(
        "leaderboard.html",
        rows=rows
    )


@app.route("/roll")
def roll():

    if session.get("winner", 0) != 0:

        return jsonify({
            "player1": session["player1"],
            "player2": session["player2"],
            "current_player": session["current_player"],
            "next_player": session["current_player"],
            "dice": 0,
            "winner": session["winner"],
            "message": "GAME OVER"
        })

    player1 = session.get("player1", 1)
    player2 = session.get("player2", 1)
    current_player = session.get("current_player", 1)

    result = subprocess.run(
        [
            "c_backend/snake_backend.exe",
            str(player1),
            str(player2),
            str(current_player)
        ],
        capture_output=True,
        text=True
    )

    output = result.stdout.strip().split("|")

    if len(output) < 7:
        return jsonify({
            "error": "Backend parsing failed",
            "raw": result.stdout
        })

    player1 = int(output[0])
    player2 = int(output[1])
    current_player = int(output[2])
    next_player = int(output[3])
    dice = int(output[4])
    winner = int(output[5])

    message = "|".join(output[6:])

    if winner == 1:
        add_win("Player 1")

    if winner == 2:
        add_win("Player 2")

    session["player1"] = player1
    session["player2"] = player2
    session["current_player"] = next_player
    session["winner"] = winner

    return jsonify({
        "player1": player1,
        "player2": player2,
        "current_player": current_player,
        "next_player": next_player,
        "dice": dice,
        "winner": winner,
        "message": message
    })


@app.route("/reset")
def reset():

    session["player1"] = 1
    session["player2"] = 1
    session["current_player"] = 1
    session["winner"] = 0

    return jsonify({
        "status": "reset"
    })


if __name__ == "__main__":
    app.run(debug=True)