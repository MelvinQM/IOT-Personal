document.addEventListener('DOMContentLoaded', function () {
    fetch('/api/player')
        .then(response => response.json())
        .then(data => {
            data.forEach(element => {
                //Create columns
                const id = document.createElement('td');
                id.className = 'p-2';
                id.textContent = element.id;
                
                const name = document.createElement('td');
                name.className = 'p-2';
                name.textContent = element.name;
                
                // Create a row
                const row = document.createElement('tr');
                row.className = 'hover:bg-gray-50 border-t-2 border-gray-100';
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

                console.log(element)
                //Create columns
                const id = document.createElement('td');
                id.className = 'p-2';
                id.textContent = element.id;
                
                const sessionId = document.createElement('td');
                sessionId.className = 'p-2';
                sessionId.textContent = element.session_id;
                
                const score = document.createElement('td');
                score.className = 'p-2';
                score.textContent = element.score;
                
                // Create a row
                const row = document.createElement('tr');
                row.className = 'hover:bg-gray-50 border-t-2 border-gray-100';
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
});
