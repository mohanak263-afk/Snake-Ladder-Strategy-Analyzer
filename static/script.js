const rollBtn = document.getElementById("rollBtn");
const resetBtn = document.getElementById("resetBtn");

const token1 = document.getElementById("player1Token");
const token2 = document.getElementById("player2Token");

function getPosition(square)
{
    if(square < 1)
    {
        square = 1;
    }

    square--;

    let row = Math.floor(square / 10);
    let col = square % 10;

    if(row % 2 === 1)
    {
        col = 9 - col;
    }

    const cellSize = 80;

    return {
        x: col * cellSize + 20,
        y: (9 - row) * cellSize + 20
    };
}

function moveToken(token, square)
{
    const pos = getPosition(square);

    token.style.left = pos.x + "px";
    token.style.top = pos.y + "px";
}

moveToken(token1, 1);
moveToken(token2, 1);

rollBtn.addEventListener("click", async () =>
{
    const response = await fetch("/roll");
    const data = await response.json();

    if(data.error)
    {
        alert(data.error);
        return;
    }

    document.getElementById("player1").innerText =
        data.player1;

    document.getElementById("player2").innerText =
        data.player2;

    document.getElementById("turn").innerText =
        "Player " + data.next_player + " Turn";

    document.getElementById("dice").innerText =
        "Dice: " + data.dice;

    document.getElementById("messageBox").innerText =
        data.message;

    const historyList =
        document.getElementById("historyList");

    const item =
        document.createElement("li");

    item.innerText =
        data.message;

    historyList.prepend(item);

    moveToken(token1, data.player1);
    moveToken(token2, data.player2);

    if(data.winner === 1)
    {
        document.getElementById("winner").innerText =
            "🏆 Player 1 Wins!";

        rollBtn.disabled = true;
    }

    if(data.winner === 2)
    {
        document.getElementById("winner").innerText =
            "🏆 Player 2 Wins!";

        rollBtn.disabled = true;
    }
});

resetBtn.addEventListener("click", async () =>
{
    await fetch("/reset");

    document.getElementById("player1").innerText = "1";
    document.getElementById("player2").innerText = "1";

    document.getElementById("turn").innerText =
        "Player 1 Turn";

    document.getElementById("dice").innerText =
        "Dice: -";

    document.getElementById("winner").innerText =
        "";

    document.getElementById("messageBox").innerText =
        "Welcome to Snake & Ladder!";

    document.getElementById("historyList").innerHTML =
        "";

    rollBtn.disabled = false;

    moveToken(token1, 1);
    moveToken(token2, 1);

    location.reload();
});