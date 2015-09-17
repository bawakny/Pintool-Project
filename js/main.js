$('.book').click(function(){
	
	$('.menu ul li').removeClass("selected");
	$('.bookFrame').css("display", "block");
	$('.book').addClass("selected");
	$('article').css("display", "none");
});


$('.article').click(function(){
	
	$('.menu ul li').removeClass("selected");
	$('.bookFrame').css("display", "none");
	$('article').css("display", "block");
	$('.article').addClass("selected");
	
});