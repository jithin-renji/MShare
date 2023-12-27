const messageInput = document.getElementById("message-input");
messageInput.addEventListener("keyup", (event) => {
  if (event.key === "Enter") {
    let message = messageInput.value;
    console.log(message)
    const lineBreak = document.createElement("br");
    const chatArea = document.querySelector(".main");
    const msgSpan = document.createElement("span");
    msgSpan.innerHTML = `${message}`;
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
