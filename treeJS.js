
$(document).ready(function(){
   var c = $("#canv")[0].getContext("2d");
   var requestAnimationFrame = window.requestAnimationFrame ||
         window.mozRequestAnimationFrame ||
         window.webkitRequestAnimationFrame ||
         window.msRequestAnimationFrame;
       
   var cancel = window.cancelAnimationFrame || 
         window.mozCancelAnimationFrame ||
         window.webkitCancelAnimationFrame ||
         window.oCancelAnimationFrame ||
         window.msCancelAnimationFrame;
   var rAF;
   var r = 7;
   var len = 50;
   var ang = 0;
   var a = parseInt( $("input").val() ) ;
   var arr = [];
   var color = 160;
   //arr.push( new Line(1500,1500,ang) );
   
   while(ang<361)
   {
       arr.push( new Line(1500,1500,ang) );
       ang = ang + 36;
   }
   

   
   
   function clear(){
      c.fillStyle = "white";
      c.fillRect(0,0,1500,1500);
   }
   function Line(x,y,angle){
     this.x = x;
     this.y = y;
     this.a = angle;
     this.draw = true;
     this.len = 0;
     this.cx = Math.cos(Math.PI/180*this.a)*3;
     this.cy = Math.sin(Math.PI/180*this.a)*3;
     this.update = function(){
        this.x -= this.cx;
        this.y -= this.cy;
     }
   }
   
   function draw(){
      for(var d1=0; d1<arr.length; d1++){  
       c.beginPath();
       c.arc(arr[d1].x,arr[d1].y,r,0,Math.PI*2);
       c.fillStyle = "rgba(" + Math.round(color) + ",122,80,0.9)";
       c.fill();
       
       arr[d1].len++;
       arr[d1].update();
      }
      if(color > 1){ color -= 0.5; }
   }
   
   function check(){
     var d2=0;
     while( arr[d2].len >= len ){        
         arr.push(new Line(arr[d2].x,arr[d2].y,arr[d2].a-a) );
         arr.push(new Line(arr[d2].x,arr[d2].y,arr[d2].a+a) );
         arr.shift();
       if(arr[d2].len == 0){
         len -= 3;
         if(r > 1){  r -= 0.5; }
        break;
       }
     }
   }
      drawAll();
      $(".play").slideDown(500);
     function drawAll(){
    if(len < 10){
      $(".play").slideUp(500);
      $(".end").delay(500).slideDown(500);
      cancel(rAF);
      return;
    } 
      draw();
      check();
      rAF = requestAnimationFrame(drawAll);
     } 
   
})