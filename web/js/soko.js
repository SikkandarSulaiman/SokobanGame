

var row = 10
var col = 9
var heightZoom = 50
var widthZoom = 50

var level = [
"   ####  ",
"####  ## ",
"#   $  # ",
"#  *** # ",
"#  . . ##",
"## * *  #",
" ##***  #",
"  # $ ###",
"  # @ #  ",
"  #####  "
]


$('body').on('keydown', function(e) {
    var event = window.event ? window.event : e;
    console.log(event.keyCode)
})

var width = col * widthZoom
var height = row * heightZoom

var gameArea = $('.game-area')

gameArea.css({
	'height': height + "px",
	'width': width + "px",
	'background-color': "white",
	'position': 'relative',
	'left': "calc(50% - " + width/2 + "px)",
	'top': "calc(50vh - " + height/2 + "px)"
})

var wallImage = "wall.png"
var playerImage = "player.png"
var targetImage = "target.png"
var placedImage = "placed.png"
var boxImage = "box.png"
var shockImage = "p_on_t.png"


for (var i in level) {
	for (var j in level[i]) {
		var tile = $('<div>').addClass('tile')
		var image = undefined
		switch (level[i][j]) {
		case '#':
			image = wallImage
			break
		case '@':
			image = playerImage
			break
		case '.':
			image = targetImage
			break
		case '*':
			image = placedImage
			break
		case '$':
			image = boxImage
			break
		case '+':
			image = shockImage
			break
		}
		tile.css({'background-image': 'url("images/' + image + '")'})
		tile.appendTo(gameArea)
	}
}

$('.tile').css({
	'height': heightZoom + 'px',
	'width': widthZoom + 'px',
	'background-size': '100% 100%',
	'float': 'left'
})

tile.appendTo(gameArea)