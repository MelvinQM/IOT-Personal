/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This script handles the form submission for a player. The input is validated based on name and session ID. 
 * Additionally, the script includes a function to redirect users to the admin page.
 * License: This project is licensed under the MIT License.
 */


let userForm = document.getElementById("userForm")

userForm.addEventListener("submit", (e) => {
    // Prevent page refresh
    e.preventDefault(); 

    // Get values from the form
    const name = document.getElementById("name").value;
    const sessionId = document.getElementById("sessionId").value;
    
    let isValid = true;

    if (!name) {
        document.getElementById("nameError").textContent = 'Name is required';
        isValid = false;
    }

    if (!sessionId) {
        document.getElementById("sessionIdError").textContent = "ID is required";
        isValid = false;
    } else if (sessionId <= 0) {
        document.getElementById("sessionIdError").textContent = "ID must be positive";
        isValid = false;
    } // TODO: else if (SessionId exists in database)

    if (isValid) {
        console.log("Name:", name);
        console.log("Session ID:", sessionId);
        // You can add further logic to handle the data submission here

        //TODO: check if name already exists in database
    }
})

function redirectToAdmin() {
    window.location.href = "/admin";
}