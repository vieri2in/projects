const form = document.querySelector('#searchForm');


form.addEventListener('submit', async (e) => {
    e.preventDefault();
    const images = document.getElementsByTagName('img');
    clearImages(images);
    try {
        const searchTerm = form.elements.query.value;
        const config = { params: { q: searchTerm } };
        const res = await axios.get("https://api.tvmaze.com/search/shows", config);
        addImages(res.data);
        clearImages();
    } catch (e) {
        console.log('Error!')
    }
    form.elements.query.value = '';
});

const addImages = (shows) => {
    for (let result of shows) {
        if (result.show.image) {
            const img = document.createElement('img');
            img.src = result.show.image.medium;
            document.body.append(img);
        }
    }
}
const clearImages = (imgs) => {
    if (imgs.length === 0) {
        return;
    }
    for (let item of imgs) {
        // item.remove();//I cannot delete all selected items, werid.
        item.src = '';// although a band aid solution, it works.
    }
}