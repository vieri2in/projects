const p1Button = document.querySelector('#p1Button');
const p2Button = document.querySelector('#p2Button');
const resetButton = document.querySelector('#resetButton');
const p1Score = document.querySelector('#p1Score');
const p2Score = document.querySelector('#p2Score');
const winningScoreSelect = document.querySelector('#playto');

let winningScore = 0;
let isGameOver = false;

winningScoreSelect.addEventListener('change', function () {
    winningScore = parseInt(this.value);
    reset();
});

p1Button.addEventListener('click', function (e) {
    if (isGameOver) return;
    let currentScore = parseInt(p1Score.innerText);
    if (currentScore < winningScore) {
        const newScore = currentScore + 1;
        p1Score.innerText = newScore;
        if (newScore === winningScore) {
            p1Score.classList.add("has-text-success");
            p2Score.classList.add("has-text-danger");
            isGameOver = true;
        }
    }
});
p2Button.addEventListener('click', function (e) {
    if (isGameOver) return;
    let currentScore = parseInt(p2Score.innerText);
    if (currentScore < winningScore) {
        const newScore = currentScore + 1;
        p2Score.innerText = newScore;
        if (newScore === winningScore) {
            p1Score.classList.add("has-text-success");
            p2Score.classList.add("has-text-danger");
            isGameOver = true;
        }
    }
});

resetButton.addEventListener('click', reset);

function reset(){
    p1Score.innerText = 0;
    p2Score.innerText = 0;
    p1Score.classList.remove("has-text-success", "has-text-danger");
    p2Score.classList.remove("has-text-success", "has-text-danger");
    isGameOver = false;
}