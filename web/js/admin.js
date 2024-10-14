/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This script populates HTML tables by fetching data from the api/endpoints. It creates table rows and cells for each data record and appends them 
 * to their respective table bodies: Players, Scores, Sessions, and Difficulties.
 * License: This project is licensed under the MIT License.
 */

document.addEventListener('DOMContentLoaded', function () {
    fetch('/api/player')
        .then(response => response.json())
        .then(data => {
            data.forEach(element => {
                //Create columns
                const id = document.createElement('td');
                id.textContent = element.id;
                
                const name = document.createElement('td');
                name.textContent = element.name;
                
                // Create a row
                const row = document.createElement('tr');
                row.appendChild(id);
                row.appendChild(name);
                
                // Append id and name to table body
                document.getElementById("players").appendChild(row);
            });
        })
        .catch(error => {
            console.error('Error:', error);
        });



    fetch('/api/score')
        .then(response => response.json())
        .then(data => {
            data.forEach(element => {
                //Create columns
                const id = document.createElement('td');
                id.textContent = element.id;
                
                const sessionId = document.createElement('td');
                sessionId.textContent = element.session_id;
                
                const score = document.createElement('td');
                score.textContent = element.score;
                
                // Create a row
                const row = document.createElement('tr');
                row.appendChild(id);
                row.appendChild(sessionId);
                row.appendChild(score);
                
                // Append id and name to table body
                document.getElementById("scores").appendChild(row);
            });
        })
        .catch(error => {
            console.error('Error:', error);
        });



    fetch('/api/session')
        .then(response => response.json())
        .then(data => {
            data.forEach(element => {
                //Create columns
                const id = document.createElement('td');
                id.textContent = element.id;
                
                const completed = document.createElement('td');
                completed.textContent = element.completed ? "True" : "False";
                
                const startTime = document.createElement('td');
                startTime.textContent = element.start_time;

                const endTime = document.createElement('td');
                endTime.textContent = element.end_time;
                
                const playerId = document.createElement('td');
                playerId.textContent = element.player_id;
                
                const difficultyId = document.createElement('td');
                difficultyId.textContent = element.difficulty_id;

                // Create a row
                const row = document.createElement('tr');
                row.appendChild(id);
                row.appendChild(completed);
                row.appendChild(startTime);
                row.appendChild(endTime);
                row.appendChild(playerId);
                row.appendChild(difficultyId);
                
                // Append id and name to table body
                document.getElementById("sessions").appendChild(row);
            });
        })
        .catch(error => {
            console.error('Error:', error);
        });

    fetch('/api/difficulty')
        .then(response => response.json())
        .then(data => {
            data.forEach(element => {
                //Create columns
                const id = document.createElement('td');
                id.textContent = element.id;
                
                const name = document.createElement('td');
                name.textContent = element.name;
                
                // Create a row
                const row = document.createElement('tr');
                row.appendChild(id);
                row.appendChild(name);
                
                // Append id and name to table body
                document.getElementById("difficulties").appendChild(row);
            });
        })
        .catch(error => {
            console.error('Error:', error);
        });
        
});
