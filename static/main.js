const messageInput = document.getElementById("message-input");
messageInput.addEventListener("keyup", (event) => {
  if (event.key === "Enter" && messageInput.value.length !== 0) {
    let message = messageInput.value;
    console.log(message)
    const lineBreak = document.createElement("br");
    const chatArea = document.getElementById("messages");
    const msgSpan = document.createElement("span");
    msgSpan.innerHTML = `<span style="color: red;">You:</span> ${message}`;
    chatArea.appendChild(msgSpan);
    chatArea.appendChild(lineBreak);

    messageInput.value = "";
    fetch("/forward", {
      method: "POST",
      credentials: "include",
      body: JSON.stringify({msg: message}),
      cache: "no-cache",
      headers: new Headers({
        "content-type": "application/json"
      })
    });
  }
});

function hideOrShowNewContactForm() {
  const newContactForm = document.getElementById("new-contact-form");
  const newContactBtn = document.getElementById("new-contact-btn");
  if (newContactForm.style.display === "none") {
    newContactBtn.innerHTML = "- New Contact";
    newContactForm.style.display = "block";
  } else {
    newContactBtn.innerHTML = "+ New Contact";
    newContactForm.style.display = "none";
  }
}

var contacts = []
function addContact() {
  const contactNameInput = document.getElementById("contact-name");
  const contactPubkeyInput = document.getElementById("contact-pubkey");
  hideOrShowNewContactForm();

  const newChat = document.createElement("a");
  newChat.innerHTML = `${contactNameInput.value}`;
  newChat.onclick = chatSelected;
  document.querySelector(".chat-list").appendChild(newChat);

  contacts.push(contactNameInput.value);

  if (contacts.length === 1) {
    document.getElementById("chat-title").innerHTML = `<h2>Select the newly created chat to message ${newChat.innerHTML}.</h2>`;
  }

  contactNameInput.value = "";
  contactPubkeyInput.value = "";
}

function chatSelected() {
  document.querySelector(".message-input-container").style.display = "block";
  document.getElementById("chat-title").innerHTML = `<h2>${this.innerHTML}</h2>`;
  document.getElementById("messages").innerHTML = "";
}
