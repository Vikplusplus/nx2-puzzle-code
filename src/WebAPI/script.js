
let currentPage = 'numbered';

let currentBoardState_numbered = [],
    currentBoardState_twoColor = [],
    currentBoardState_kColor = [];

function showPage(page) {
    document.querySelectorAll('.content').forEach(p => p.classList.remove('active'));
    document.getElementById(page).classList.add('active');

    if (page === 'numbered') {
        currentPage = 'numbered';
        renderBoard(currentPage, currentBoardState_numbered);
    }
    else if (page === 'twoColor') {
        currentPage = 'twoColor';
        renderBoard(currentPage, currentBoardState_twoColor);
    }
    else {
        currentPage = 'kColor';
        renderBoard(currentPage, currentBoardState_kColor);
    }
}

document.addEventListener("keydown", (event) => {
    let direction = null;

    switch (event.key) {
        case "ArrowUp":
            direction = "U";
            break;
        case "ArrowDown":
            direction = "D";
            break;
        case "ArrowLeft":
            direction = "L";
            break;
        case "ArrowRight":
            direction = "R";
            break;
    }

    let keys = ["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight"];

    if (keys.includes(event.key)) {
        event.preventDefault();
    }

    if (direction) {
        if (currentPage === 'numbered') {
            applyMove(direction);
        }
        else if (currentPage === 'twoColor') {
            applyMove(direction);
        }
        else {
            applyMove(direction);
        }
    }
});

function getCurrentBoardState(variation) {
    if (variation === 'numbered') {
        return currentBoardState_numbered;
    }
    if (variation === 'twoColor') {
        return currentBoardState_twoColor;
    }
    return currentBoardState_kColor;
}

function setCurrentBoardState(variation, boardState) {
    if (variation === 'numbered') {
        currentBoardState_numbered = boardState;
    }
    else if (variation === 'twoColor') {
        currentBoardState_twoColor = boardState;
    }
    else {
        currentBoardState_kColor = boardState;
    }
}
async function fetchBoardState(variation) {
    const response = await fetch(`http://localhost:8080/generateInitialBoardState_${variation}`);
    const data = await response.json();
    renderBoard(variation, data.boardState);
}

function renderBoard(variation, boardState) {
    setCurrentBoardState(variation, boardState);
    const n = boardState.length / 2;

    const boardContainer = document.getElementById(`board-container_${variation}`);
    boardContainer.innerHTML = "";
    boardContainer.style.display = "grid";
    boardContainer.style.gridTemplateColumns = "repeat(2, 80px)";
    boardContainer.style.gridTemplateRows = `repeat(${n}, 80px)`;

    boardState.forEach((label) => {
        const tile = document.createElement("div");
        tile.classList.add("tile");
        if (label === 0) {
            tile.classList.add("empty");
        } else {
            tile.textContent = label;
        }
        boardContainer.appendChild(tile);
    });
}

async function applyMove(direction) {
    const variation = currentPage;
    const currentBoardState = getCurrentBoardState(variation);

    const response = await fetch("http://localhost:8080/move", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            boardState: currentBoardState,
            direction: direction
        })
    });
    const data = await response.json();
    renderBoard(variation, data.boardState);
}

async function generateState() {
    const variation = currentPage;
    const n = parseInt(document.getElementById(`amount_of_rows_${variation}`).value);
    let k = null;

    if (variation === 'numbered') {
        const optimalSolution_button = document.getElementById("optimal_solution_numbered");
        if (n > 5) {
            optimalSolution_button.disabled = true;
            optimalSolution_button.style.opacity = "0.5";
            optimalSolution_button.style.cursor = "not-allowed";
        } else {
            optimalSolution_button.disabled = false;
            optimalSolution_button.style.opacity = "1";
            optimalSolution_button.style.cursor = "pointer";
        }
    }
    else if (variation === 'kColor') {
        const optimalSolution_button = document.getElementById("optimal_solution_kColor");
        if (n > 5) {
            optimalSolution_button.disabled = true;
            optimalSolution_button.style.opacity = "0.5";
            optimalSolution_button.style.cursor = "not-allowed";
        } else {
            optimalSolution_button.disabled = false;
            optimalSolution_button.style.opacity = "1";
            optimalSolution_button.style.cursor = "pointer";
        }

        k = parseInt(document.getElementById("amount_of_colors_kColor").value);
        if (k < 3 || k > 2 * n - 2) {
            alert("k must be a number ranging from 3 to " + (2 * n - 2) + "!");
            return;
        }
        if (isNaN(k)) k = -1;

    }
    const response = await fetch(`http://localhost:8080/generateState_${variation}`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            n : n,
            k : k
        })
    });
    const data = await response.json();
    renderBoard(variation, data.boardState);
}

async function viewOptimalSolution() {
    const variation = currentPage;
    const currentBoardState = getCurrentBoardState(variation);

    const response = await fetch("http://localhost:8080/optimalSolution", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ boardState: currentBoardState })
    });

    const data = await response.json();
    const moveSequence = data.moveSequence;

    let i = 0;
    const interval = setInterval(() => {
        if (i < moveSequence.length) {
            applyMove(moveSequence[i]);
            i++;
        } else {
            clearInterval(interval);
        }
    }, 500);
}

async function viewAlgorithm(algorithm) {
    const variation = currentPage;
    const currentBoardState = getCurrentBoardState(variation);

    const response = await fetch(`http://localhost:8080/${algorithm}_${variation}`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ boardState: currentBoardState })
    });

    const data = await response.json();
    const moveSequence = data.moveSequence;

    let i = 0;
    const interval = setInterval(() => {
        if (i < moveSequence.length) {
            applyMove(moveSequence[i]);
            i++;
        } else {
            clearInterval(interval);
        }
    }, 500);

}

fetchBoardState('numbered');
fetchBoardState('twoColor');
fetchBoardState('kColor');