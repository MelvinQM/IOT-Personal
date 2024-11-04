/*
 * Author: Melvin Moes
 * Date: October 17, 2024
 * Description:
 * License: This project is licensed under the MIT License.
 */


const ApiService = {
  async getPlayerIdFromName(name) {
    return fetch(`/api/player?name=${name}`)
      .then((response) => response.json())
      .then((data) => {
        // console.log("Player id: ", data[0].id);
        return data[0].id;
      })
      .catch((error) => {
        console.error("Error:", error);
        return null;
      });
  },

  async addToSessionStart(sessionId, playerId, useGyro, difficultyId) {
    return fetch("/api/session/" + sessionId, {
      method: "PATCH",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        player_id: playerId,
        use_gyro: useGyro,
        difficulty_id: difficultyId,
        completed: false,
        start_time: getCurrentDateTime(),
      }),
    })
      .then((response) => response.json())
      .then((data) => {
        // console.log("Updated session: ", data);
      })
      .catch((error) => {
        console.error("Error:", error);
        return null;
      });
  },

  async addToSessionEnd(endTime, sessionId) {
    return fetch("/api/session/" + sessionId, {
      method: "PATCH",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        end_time: endTime
      }),
    })
      .then((response) => response.json())
      .then((data) => {
        // console.log("Updated session: ", data);
      })
      .catch((error) => {
        console.error("Error:", error);
        return null;
      });
  },

  async fetchSessionData(sessionId) {
    return fetch("/api/session/" + sessionId)
      .then((response) => response.json())
      .then((data) => {
        // console.log("Fetched session: ", data);
        return data;
      })
      .catch((error) => {
        console.error("Error fetching session:", error);
        return null;
      });
  },
  
  async fetchScoreBySessionId(sessionId) {
    return fetch(`/api/score?session_id=${sessionId}`)
      .then((response) => response.json())
      .then((scores) => {
        // console.log("Fetched scores: ", scores);
        return scores;
      })
      .catch((error) => {
        console.error("Error fetching scores:", error);
      });
  },

  async createPlayer(name) {
    return fetch("/api/player", {
      method: "POST",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ name: name }),
    })
      .then((response) => response.json())
      .then((data) => {
        // console.log(data);
        return data.id;
      })
      .catch((error) => {
        console.error("Error:", error);
        return null;
      });
  },
}

function getDifficultyName(difficultyId) {
  switch (difficultyId) {
    case 1:
      return "EASY";
    case 2:
      return "NORMAL";
    case 3:
      return "HARD";
    default:
      return "UNKNOWN";
  }
}

function redirectToAdmin() {
  window.location.href = "/admin";
}

function toggleDivs() {
  var inputScreen = document.getElementById("input-screen");
  var playingScreen = document.getElementById("playing-screen");
  var scoreScreen = document.getElementById("score-screen");

  inputScreen.classList.toggle("d-none");
  inputScreen.classList.toggle("d-block");

  playingScreen.classList.toggle("d-none");
  playingScreen.classList.toggle("d-block");
  scoreScreen.classList.toggle("d-none");
  scoreScreen.classList.toggle("d-block");
}

function getCurrentDateTime() {
  const now = new Date();

  const year = now.getFullYear();
  const month = String(now.getMonth() + 1).padStart(2, "0"); // Months are zero-based
  const day = String(now.getDate()).padStart(2, "0");
  const hours = String(now.getHours()).padStart(2, "0");
  const minutes = String(now.getMinutes()).padStart(2, "0");
  const seconds = String(now.getSeconds()).padStart(2, "0");

  return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
}

const openPlayingScreen = async (sessionId, name) => {
  // Switch views
  toggleDivs();

  // Make initial call to fetch session data
  let sessionData = await ApiService.fetchSessionData(sessionId);

  // Insert data into table
  const nameElement = document.getElementById("info-player-name");
  const sessionIdElement = document.getElementById("info-session-id");
  const difficultyIdElement = document.getElementById("info-difficulty");
  const controlMethodElement = document.getElementById("info-control-method");
  const startTimeElement = document.getElementById("info-start-time");
  const endTimeElement = document.getElementById("info-end-time");
  const statusElement = document.getElementById("info-status");

  nameElement.textContent = name;
  sessionIdElement.textContent = sessionId;
  difficultyIdElement.textContent = getDifficultyName(sessionData.difficulty_id);
  controlMethodElement.textContent = sessionData.use_gyro ? "Gyro" : "Joystick";
  startTimeElement.textContent = sessionData.start_time;
  endTimeElement.textContent = sessionData.end_time
    ? sessionData.end_time
    : "Ongoing";

  const scoreElement = document.getElementById("info-scores");

  // Start fetching every 10 seconds for scores connected to session id
  const fetchInterval = setInterval(async () => {
    let scoreData = await ApiService.fetchScoreBySessionId(sessionId);
    if (scoreData.length > 0) {
      scoreElement.innerHTML = ""; // Clear previous data
      scoreData.forEach((data) => {
        let tr = document.createElement("tr");
        let td = document.createElement("td");
        td.textContent = data.score;
        tr.appendChild(td);
        scoreElement.appendChild(tr);
      });
    } else {
      console.log("No score data found");
    }

    let sessionData = await ApiService.fetchSessionData(sessionId);
    if (sessionData) {
      if (sessionData.end_time) {
        endTimeElement.textContent = sessionData.end_time;
      }
      if (sessionData.completed) {
        statusElement.textContent = "Completed";
        statusElement.parentElement.classList.toggle("text-danger");
        statusElement.parentElement.classList.toggle("text-success");
        
        // Stop fetching when game is completed
        let endTime = getCurrentDateTime();
        endTimeElement.textContent = endTime;
        await ApiService.addToSessionEnd(endTime, sessionId);
        
        clearInterval(fetchInterval);
      }
    } else {
      console.error("No session data found");
    }
  }, 10000);
};


let userForm = document.getElementById("user-form");

userForm.addEventListener("submit", async (e) => {
  // Prevent page refresh
  e.preventDefault();

  // Get values from the form
  const name = document.getElementById("name").value;
  const sessionId = document.getElementById("session-id").value;
  const difficulty_id = document.getElementById("difficulty-id").value;
  const enableGyro = document.getElementById("enable-gyro").checked;

  let isValid = true;
  if (!name) {
    document.getElementById("name-error").textContent = "Name is required";
    isValid = false;
  }
  if (!sessionId) {
    document.getElementById("session-id-error").textContent = "ID is required";
    isValid = false;
  } else if (sessionId <= 0) {
    document.getElementById("session-id-error").textContent =
      "ID must be positive";
    isValid = false;
  }

  if (isValid) {
    // Usage of getPlayerId
    let playerId = await ApiService.getPlayerIdFromName(name);

    if (!playerId) {
      console.log(
        "No existing player found - Creating new player and adding to session...."
      );
      playerId = await ApiService.createPlayer(name);
    } else {
      // Player already exists
      console.log("Player already exists, adding to session....");
    }

    await ApiService.addToSessionStart(sessionId, playerId, enableGyro, difficulty_id);
    await openPlayingScreen(sessionId, name);
  }
});
