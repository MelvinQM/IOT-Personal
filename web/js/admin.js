/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This script populates HTML tables by fetching data from the api/endpoints. It creates table rows and cells for each data record and appends them 
 * to their respective table bodies: Players, Scores, Sessions, and Difficulties.
 * License: This project is licensed under the MIT License.
 */

const ApiService = {
    async fetchData(endpoint, tableId, columns){
        return fetch(endpoint)
            .then(response => response.json())
            .then(data => {
                data.forEach(element => {
                    // Create a row
                    const row = document.createElement('tr');
                    
                    // Populate row based on specified columns
                    columns.forEach(col => {
                        const cell = document.createElement('td');
                        cell.textContent = typeof col === 'function' ? col(element) : element[col];
                        row.appendChild(cell);
                    });
                    
                    // Append row to the table body
                    document.getElementById(tableId).appendChild(row);
                });
            })
            .catch(error => {
                console.error('Error:', error);
            });
    }
}

document.addEventListener('DOMContentLoaded', function () {
    ApiService.fetchData('/api/player', 'players', ['id', 'name']);
    ApiService.fetchData('/api/score', 'scores', ['id', 'session_id', 'score']);
    ApiService.fetchData('/api/session', 'sessions', ['id', element => element.completed ? "True" : "False", 'start_time','end_time','player_id','difficulty_id']);
    ApiService.fetchData('/api/difficulty', 'difficulties', ['id', 'name']);
    ApiService.fetchData('/api/actions/gethighscores', 'highscores', ['name', 'score']);
});