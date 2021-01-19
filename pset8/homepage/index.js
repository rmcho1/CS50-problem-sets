function launch(option) {
    window.location = option.value;
}           

/*In about me page, golden gate bridge image*/
function blink() {
    let movies = document.querySelector('.movies-title');
    if (movies.style.visibility === 'hidden') {
        movies.style.visibility = 'visible'
    }
    else {
        movies.style.visibility = 'hidden';
    }
}
window.setInterval(blink, 900);