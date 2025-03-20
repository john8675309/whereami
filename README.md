# Where Am I

A lightweight C utility that provides detailed information about your current system environment and connection status.

## Overview

"Where Am I" displays comprehensive information about your system, including connection details, user environment, and hardware specifications. It's particularly useful for system administrators managing multiple servers or users who frequently switch between different environments.

## Features

- **System Information**
  - Hostname
  - Operating system name and version
  - Kernel version
  - Architecture
  - Current date and time

- **User Environment**
  - Current username
  - Working directory
  - Shell type
  - Terminal emulator

- **Connection Details**
  - Connection type (local or SSH)
  - SSH source IP address (when connected remotely)
  - SSH TTY information
  - X Display configuration (if applicable)
  - Session type

## Output Example

```
╭─────────── WHERE AM I? ───────────╮

=== System Information ===
Hostname      : server-db-01
System        : Linux 5.15.0-41-generic
Kernel Version: #44-Ubuntu SMP Wed Jul 13 14:24:35 UTC 2022
Architecture  : x86_64
Date & Time   : 2025-03-20 15:42:33

=== User Information ===
User          : admin
Working Dir   : /home/admin/projects
Shell         : /bin/bash
Terminal      : xterm-256color

=== Connection Information ===
Connection    : Remote SSH
SSH Source    : 192.168.1.25
SSH TTY       : /dev/pts/0
╰─────────────────────────────────╯
```

## Installation

### Prerequisites
- GCC or compatible C compiler
- Linux-based operating system

### Compiling from Source
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/whereami.git
   cd whereami
   ```

2. Compile using make:
   ```bash
   make
   ```

3. Optionally, install system-wide:
   ```bash
   sudo make install
   ```

## Usage

Simply run the executable:

```bash
whereami
```

No command-line arguments are needed.

## Why Use Where Am I?

- **Server Management**: Quickly identify which server you're working on in multi-server environments
- **Security**: Verify SSH connection details to ensure you're connected to the expected system
- **Troubleshooting**: Gather relevant system information in a single view for debugging purposes
- **Documentation**: Easily capture system specifications for documentation or support tickets

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
