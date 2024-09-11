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
                row.appendChild(id);
                row.appendChild(name);
                
                // Append id and name to table body
                document.getElementById("players").appendChild(row);
            });
        })
        .catch(error => {
            console.error('Error:', error);
        });
});
