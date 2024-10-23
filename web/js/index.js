/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This script handles the form submission for a player. The input is validated based on name and session ID.
 * Additionally, the script includes a function to redirect users to the admin page.
 * License: This project is licensed under the MIT License.
 */

const getPlayerIdFromName = (name) => {
  return fetch(`/api/player?name=${name}`)
    .then((response) => response.json())
    .then((data) => {
      const playerId = data[0].id;
      console.log(playerId);
      return playerId;
    })
    .catch((error) => {
      console.error("Error:", error);
      return null;
    });
};

const addToSession = (sessionId, playerId, useGyro, difficultyId) => {
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
      start_time: new Date(),
    }),
  })
    .then((response) => response.json())
    .then((data) => {
      console.log("Updated session: ", data);
    })
    .catch((error) => {
      console.error("Error:", error);
      return null;
    });
};

const createPlayer = (name) => {
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
      console.log(data);
      return data[0].id;
    })
    .catch((error) => {
      console.error("Error:", error);
      return null;
    });
};

let userForm = document.getElementById("userForm");

userForm.addEventListener("submit", async (e) => {
  // Prevent page refresh
  e.preventDefault();

  // Get values from the form
  const name = document.getElementById("name").value;
  const sessionId = document.getElementById("sessionId").value;
  const difficulty_id = document.getElementById("difficultyId").value;
  const enableGyro = document.getElementById("enableGyro").value;

  let isValid = true;

  if (!name) {
    document.getElementById("nameError").textContent = "Name is required";
    isValid = false;
  }

  if (!sessionId) {
    document.getElementById("sessionIdError").textContent = "ID is required";
    isValid = false;
  } else if (sessionId <= 0) {
    document.getElementById("sessionIdError").textContent =
      "ID must be positive";
    isValid = false;
  }


  if (isValid) {
    console.log("Name:", name);
    console.log("Session ID:", sessionId);

    // Usage of getPlayerId
    let playerId = await getPlayerIdFromName(name);

    if (playerId) {
      console.log("ID found: ", playerId);
    } else {
      console.log("No ID found.");
    }

    if (!playerId) {
      console.log(
        "No existing player found - Creating new player and adding to session...."
      );
      playerId = await createPlayer(name);
    } else {
      // Player already exists
      console.log("Player already exists, adding to session....");
    }

    await addToSession(sessionId, playerId, enableGyro, difficulty_id);
  }
});

function redirectToAdmin() {
  window.location.href = "/admin";
}
