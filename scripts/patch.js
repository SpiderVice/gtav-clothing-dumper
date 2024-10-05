const fs = require('fs/promises');

Promise.all([
    fs.readFile('./dist/clothingdump.json', { encoding: 'utf8' }).then((baseJson) => new Promise((resolve, reject) => {
        try {
            resolve(JSON.parse(baseJson))
        } catch (err) {
            reject(err);
        }
    })),
    fs.readdir('./patches/').then((patchFiles) => Promise.all(patchFiles.map((patchFile) => fs.readFile(`./patches/${patchFile}`, { encoding: 'utf8' }).then((patchJson) => {
        return new Promise((resolve, reject) => {
            try {
                resolve(JSON.parse(patchJson));
            } catch (err) {
                reject(err);
            }
        })
    }))))
]).then(([baseJson, patches]) => {
    console.log(patches)
    patches.forEach((patch) => {
        Object.entries(patch).forEach(([pedName, comps]) => {
            Object.entries(comps).forEach(([compName, drawables]) => {
                Object.entries(drawables).forEach(([drawableId, textures]) => {
                    Object.entries(textures).forEach(([textureId, data]) => {
                        baseJson[pedName][compName][drawableId] ??= {};
                        baseJson[pedName][compName][drawableId][textureId] = data;
                    })
                })
            })
        })
    });

    fs.writeFile('./dist/clothingdump.patched.json', JSON.stringify(baseJson, undefined, 4));
})
