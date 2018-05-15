
var heightZoom = 100
var widthZoom = 100

var gameArea = $('.game-area')

var wallImage = "wall.png"
var playerImage = "player.png"
var targetImage = "target.png"
var placedImage = "placed.png"
var boxImage = "box.png"
var shockImage = "p_on_t.png"

$('body').on('keydown', function(e) {
    var event = window.event ? window.event : e;
    console.log(event.keyCode)

    var cmd = '/cmd='

    if (event.keyCode == 37)
    	cmd += 'a'
    else if (event.keyCode == 38)
    	cmd += 'w'
    else if (event.keyCode == 39)
    	cmd += 'd'
    else if (event.keyCode == 40)
    	cmd += 's'
    else if (event.keyCode == 13)
    	cmd += 'b'
    else if (event.keyCode == 78)
    	cmd += 'n'
    else if (event.keyCode == 82)
    	cmd += 'r'
    else
    	return


    $.get(cmd, function(data) {
    	var raw = data.split('\n')[0]
    	jsonData = JSON.parse(raw)

    	var level = jsonData['map']
	var row = jsonData['row']
	var col = jsonData['col']


	var width = col * widthZoom
	var height = row * heightZoom

    	var tile
    	gameArea.empty()

	for (var i in level) {
		for (var j in level[i]) {
		    tile = $('<div>').addClass('tile')
		    
		    	var shrink = false
			var image = undefined
			switch (level[i][j]) {
			case '#':
				image = wallImage
				break
			case '@':
				image = playerImage
				break
			case '.':
				shrink = true
				image = targetImage
				break
			case '*':
				shrink = true
				image = placedImage
				break
			case '$':
				shrink = true
				image = boxImage
				break
			case '+':
				image = shockImage
				break
			}
		    	tile.css({
				'background-image': 'url("images/' + image + '")',
			})
		    	if (shrink === true)
		    		tile.css({
					'background-size': '50% 50%',
					'background-repeat': 'no-repeat',
					'background-position': '50%'		    			
		    		})
		    	else
		    		tile.css({
					'background-size': '100% 100%',		    			
		    		})
			tile.appendTo(gameArea)
		}
	}

	tile.appendTo(gameArea)

	gameArea.css({
		'height': height + "px",
		'width': width + "px",
		'background-color': "white",
		'position': 'relative',
		'left': "calc(50% - " + width/2 + "px)",
		'top': "calc(50vh - " + height/2 + "px)"
	})

	$('.tile').css({
		'height': heightZoom + 'px',
		'width': widthZoom + 'px',
		'float': 'left'
	})

    })
})


