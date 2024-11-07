/*
 * Author: Melvin Moes
 * Date: November 5, 2024
 * Description: This script populates HTML tables by fetching data from the api/endpoints. It creates table rows and cells for each data record and appends them 
 * to their respective table bodies: Players, Scores, Sessions, and Difficulties.
 * License: This project is licensed under the MIT License.
 */

const interval = 5000;

const ApiService = {
    async fetchData(endpoint, tableId, columns) {
        return fetch(endpoint)
            .then(response => response.json())
            .then(data => {
                const tableBody = document.getElementById(tableId);

                // Clear table before filling in data
                tableBody.innerHTML = '';

                data.forEach(element => {
                    const row = document.createElement('tr');
                    
                    // Populate row based on specified columns
                    columns.forEach(col => {
                        const cell = document.createElement('td');
                        cell.textContent = typeof col === 'function' ? col(element) : element[col];
                        row.appendChild(cell);
                    });
                    
                    // Append row to the table body
                    tableBody.appendChild(row);
                });
            })
            .catch(error => {
                console.error('Error:', error);
            });
    }
}

const fetchAllData = () => {
    ApiService.fetchData('/api/player', 'players', ['id', 'name']);
    ApiService.fetchData('/api/score', 'scores', ['id', 'session_id', 'score']);
    ApiService.fetchData('/api/session', 'sessions', ['id', element => element.completed ? "True" : "False", 'start_time', 'end_time', 'player_id', 'difficulty_id']);
    ApiService.fetchData('/api/difficulty', 'difficulties', ['id', 'name']);
    ApiService.fetchData('/api/actions/gethighscores', 'highscores', ['name', 'score']);
}

document.addEventListener('DOMContentLoaded', function () {
    fetchAllData();
    setInterval(() => {
        fetchAllData();
    }, interval);
});
