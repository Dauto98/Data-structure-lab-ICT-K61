const fs = require("fs");

for (var i = 1; i < 101; i++) {
	fs.appendFileSync("vi-practice.txt", i + "\n");
}
