import subprocess

actions = [
    "client1 connects",
    "client1 /donate 0 50",
    "client1 logout",
    "client2 connects",
    "client2 /donate 1 100",
    "client2 logout",
    "client3 connects",
    "client3 /donate 2 150",
    "client3 logout",
    "client4 connects",
    "client4 /donate 3 200",
    "client4 logout",
    "client5 connects",
    "client5 /top",
    "client5 logout",
]

clients: dict[str, subprocess.Popen] = {}

for action in actions:
    client, action = action.split(" ", 1);

    if action == "connects":
        client_proc = subprocess.Popen(
            ["./zotDonate_client", "0.0.0.0", "19020"],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )

        clients[client] = client_proc
    else:
        if action == "logout":
            clients[client].stdin.write("/logout\n")
            clients[client].stdin.flush()
            clients.pop(client)
        else:
            clients[client].stdin.write(action + "\n");
            clients[client].stdin.flush()
