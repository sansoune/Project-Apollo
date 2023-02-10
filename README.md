# Projet-Apollo
This database management system is designed to store and manage large data files (1GB each) used for training Artificial Intelligence models. The system is part of an ecosystem for creating AI, and its primary focus is to provide an easy and efficient way to download, train, and delete data files.

## Features
- Store and manage 1GB data files
- Easy download and deletion of data files
- Secure and efficient data storage

## Installation
1. Clone the repository
``` bash
git clone https://github.com/sansoune/Project-Apollo
```

2. install jansson 
``` bash
sudo apt install libjansson-dev
```

3. compile the app
``` bash
gcc -o Apollo backend/main.c backend/dbms.c -ljansson
```

3. run the frontend
```bash
cd /frontend
npm i
node server.js
```

## Contributing
We welcome contributions to this project! If you have any suggestions or improvements, feel free to submit a pull request.


## Licence
This project is licensed under the [MIT License](LICENSE). This license allows for free use, distribution, and commercial use. It is a permissive open source license and a good choice for starting an open source project.