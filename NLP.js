const fs = require(`fs`);

console.log(`[${new Date().toJSON()}] Start script`);

fs.readFile(`./commons.txt`, (err, data) => {
    if (err) throw err;
    let commons = data.toString().split(`\r\n`);

    let combinations = {
        two: {
            0: {}
        },
        three: {}
    };

    commons.forEach(word => {
        if (word.length >= 2) {
            for (let i = 0; i < word.length - 1; i++) {
                combinations[`two`][0][word.substr(i, 2)] == undefined
                    ? combinations[`two`][0][word.substr(i, 2)] = {value: 1}
                    : combinations[`two`][0][word.substr(i, 2)].value++
            }
        }
        if (word.length >= 3) {
            for (let i = 0; i < word.length - 2; i++) {
                combinations[`three`][word.substr(i, 3)] == undefined
                    ? combinations[`three`][word.substr(i, 3)] = {value: 1}
                    : combinations[`three`][word.substr(i, 3)].value++
            }
        }
    });
    fs.writeFile(`./output.json`, JSON.stringify(combinations, null, 2), err => {
        if (err) throw err;
    });
});
