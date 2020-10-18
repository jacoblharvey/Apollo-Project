// printer ready version of the robot


module oneSnap(){
  servoMPT = 2.5;   // servo mounting plate thickness
  mpt = servoMPT + 0.4;  // servo slot
  springT = 1.6; 

  difference(){
    translate([0,0,0])cube([4,16,18]);
    translate([-1,3.75,4]) cube([6,mpt,12.5]);
    translate([-1,4.75,2]) cube([6,mpt-1,18]);

    translate([-1,3.75+mpt+springT,2]) cube([6,4.0,20]);
  }    
  translate([0,6.7,0])cube([4,2,5.]);  
}



module snapJoint(servoRot,armRot){
  ys = 5;
  zs = 7.7+1.5;
  translate([11.75,0,1.99])oneSnap();
  translate([-15.75,0,1.99])oneSnap();
  translate([0,3+ys,zs-7.7])cube([31.5,16,3],center=true);

  /**
    
    if(servoRot == 1){
    translate([-5,22.2,12.2])rotate([90,0,0])color("blue")servo(armRot);
  } else {
    translate([5,22.2,12.2])rotate([90,180,0])color("red")servo(armRot);
  }

*/


}



module frame(){ // 80x100
  cube([5,125,5]);
  cube([85,5,5]);
  translate([80,0,0])cube([5,125,5]);
  translate([0,125,0])cube([85,5,5]);
  translate([0,20,0])rotate([0,0,-90])snapJoint(1,120);
  translate([85,20,0])rotate([0,0,90])snapJoint(0,120);

   // translate([0,36,25])cube([85,55,10]);   // breadboard

    translate([0,80,0])cube([5,5,20]);  // post
    translate([80,80,0])cube([5,5,20]);  // post
    translate([0,40,0])cube([5,5,20]); // post
    translate([80,40,0])cube([5,5,20]); // post
    
    translate([0,105,0])cube([85,5,5]); //underside support back
    translate([0,100,0])cube([85,5,5]);
    
    translate([0,30,0])cube([85,5,5]); // underside support front
    translate([0,25,0])cube([85,5,5]);
    
    translate([0,125,0])cube([5,5,20]);// 4 posts for holding power supply
    translate([0,100,0])cube([5,5,20]);
    translate([80,125,0])cube([5,5,20]);
    translate([80,100,0])cube([5,5,20]);
}




module supportFrame(){ //This is for the top support for the bboard
    
  translate([0,125,30])cube([85,5,5]);
    
    
    }

module rail(){ // rail that the frame slides on 
   difference(){
    translate([0,0,0])rotate([0,90,0])cylinder(d=70,h=5,$fn=64);
    translate([-2,0,0])rotate([0,90,0])cylinder(d=60,h=10,$fn=64);
    translate([-5,-35,0])cube([25,75,40]);
   }
    }


module wheelLeft(){ //left wheel
    translate([0,0,13])rotate([0,90,0])cylinder(d=100,h=5,$fn=64);
    
    }



//wheelLeft();
//translate([80,95,0])railTwo();
//translate([0,95,0]) this is the translation for the rail
//translate([-20,0,0]) this is the translation for the snap joint
    //this translation just moves it out of the way so its legible.
    
    
 //PRINT THE FOLLOWING
    
//print 2 rails separately
rail();

//Print the frame
frame();

//print 2 of these supports
supportFrame();
    
// print 2 of these snap joints    
snapJoint();
