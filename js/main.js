$('.book').click(function(){
	
	$('.menu ul li').removeClass("selected");
	
	$('.book').addClass("selected");
	$('.bookFrame').css("display", "block");
	$('article').css("display", "none");
	$('.driveLink').css("display", "none");
});


$('.article').click(function(){
	
	$('.menu ul li').removeClass("selected");
	
	
	$('.article').addClass("selected");
	$('.bookFrame').css("display", "none");
	$('article').css("display", "block");
	$('.driveLink').css("display", "none");
	
});

$('.drive').click(function(){
	
	$('.menu ul li').removeClass("selected");
	$('.bookFrame').css("display", "none");
	$('article').css("display", "none");
	$('.driveLink').css("display", "block");
	$('.article').addClass("selected");
	
});