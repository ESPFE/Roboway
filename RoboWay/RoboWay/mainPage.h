/*!
    \file		mainPage.h
	\brief		This file is only for documenting purposes
	\warning    Insert no program code here
	\author		Andre S&uuml;nnemann ( a.suennemann@edv-peuker.de | <a href="http://www.edv-peuker.de" target="_blank">www.edv-peuker.de</a> )
	\date		20.03.2014
	\version	1.3.5
	
	\copyright	"THE BEER-WARE LICENSE" (Revision 42):\n
				<a.suennemann@edv-peuker.de> wrote this file.\n
				As long as you retain this notice you can do whatever you want with this stuff.\n
				If we meet some day, and you think this stuff is worth it, you can buy me a beer in return Andre S&uuml;nnemann.


    \mainpage       This is the documentation for developers and people interested in functionality of RoboWay - Inverted Pendulum

    \brief          <h2>RoboWay is an educational project.</h2>
					Its body and its wheels are 3d printed.\n
					The two controller boards are self made.\n\n
					I've chosen this project because of the limitations of micro controllers.\n
					I think today you can realize almost everything if you have enough resources.\n
					So normally you don't have to care about the efficiency of your algorithms and programs.\n\n
					
					But an inverted pendulum such as RoboWay is very time-critical and you have to write very efficient and lightweight code because of the limitations of embedded hardware.\n\n
					
					A video is available <a href="https://www.youtube.com/watch?v=RWkzlugv2Mk">here</a>

                    <div class="doubleImage">
                        <img src="../images/RoboWayFront.jpg" alt="RoboWay Front View" style="width: 60%; margin: 10px 20%;" />
                        <img src="../images/RoboWayBack.jpg" alt="RoboWay Back View" style="width: 60%; margin: 10px 20%;" />
                        <div class="clear"></div>
                    </div>

                    <p><br/></p>

                    <h2>Used electronic components</h2>
                    <ul style="list-style-type: none;">
                        <li style="margin-bottom: 40px;">
                            <div style="float:left; margin-right: 5%;">
                                <b>Sonar sensor SRF08\n</b>
								Actually not assembled\n\n
                                See \ref srf08.h\n
                                See \ref srf08.c\n
                            </div>
                            <div style="float:right; width: 50%; min-width:225px;">
                            <img src="../images/srf08.png" alt="Sonar sensor SRF08" style="width:225px"/>
                            </div>
                            <div class="clear"></div>
                        </li>
                        <li style="margin-bottom: 40px;">
                            <div style="float:left; margin-right: 5%;">
                            <b>9 degrees of freedom IMU GY80\n\n</b>
                            Three axis accelerometer ADXL354\n
                            See \ref adxl354.h\n
                            See \ref adxl354.c\n\n
                            Three axis gyroscope L3G4200D\n
                            See \ref l3g4200d.h\n
                            See \ref l3g4200d.c\n\n
                            </div>
                            <div style="float:right; width: 50%; min-width:225px;">
                            <img src="../images/gy80.jpg" alt="9DOF IMU GY80" style="width:225px" />
                            </div>
                            <div class="clear"></div>
                        </li>
                        <li style="margin-bottom: 40px;">
                            <div style="float:left; margin-right: 5%;">
                                <b>Micro controller <a href="http://www.atmel.com/devices/atmega328p.aspx" target="_blank">AtMaga 328P</a></b>\n\n
                                \ref i2cmaster.h\n
                                \ref i2cmaster.c\n
                                \ref usart.h\n
                                \ref usart.c\n
                                \ref avrConstants.h\n
                                \ref avrConstants.c\n\n
                            </div>
                            <div style="float:right; width: 50%; min-width:225px;">
                            <img src="../images/AtMega328P.jpg" alt="Microcontroller AtMega 328P" style="width:225px" />
                            </div>
                            <div class="clear"></div>
                        </li>
                        <li style="margin-bottom: 40px;">
                            <div style="float:left; margin-right: 5%;">
                                <b>DC motor driver L293D</b>\n\n
                                \ref motorControll.h\n
                                \ref motorControll.c\n\n
                            </div>
                            <div style="float:right; width: 50%; min-width:225px;">
                            <img src="../images/L293D.jpg" alt="Motor driver L293D" style="width:225px" />
                            </div>
                            <div class="clear"></div>
                        </li>
                    </ul>

                    <p><br/></p>

                    <h2>Wiring diagrams:</h2>
                    <div style="text-align: center;">
                        <img src="../images/BoardPower.png" alt="Wiring diagram of the voltage regulator and the motor controller" style="width:90%; margin: 10px 5%;"/>Voltage regulator and motor controller
                        <img src="../images/BoardCTL.png" alt="Wiring diagram of the micro controller board and sensors" style="width:90%; margin: 10px 5%;"/>Micro controller board and sensors
                    </div>


                    <p><br /><br /></p>
                    <div>
                        <h2>How does RoboWay works</h2>
                        <div style="float: left; width:50%">
                            As you can see in the diagram below RoboWay uses an accelerometer and a gyroscope with a complementary filter to calculate its angular position.\n
                            The angular position and a reference ( \ref BALANCE_REF ) value is the input for a PID controller.\n
                            The output of the PID is used as PWM output for the motor control ( \ref motorControll.h ).
                        </div>
                        <div style="float: left; width:50%;">
                            <img src="../images/HowStuffWorks.png" alt="How RoboWay works" style="width:90%; margin: 10px 5%;"/>
                        </div>
                    </div>
                    <div class="clear"></div>
					
					<p><br/></p>
					<p><br/></p>
					
					<h2>Future versions of RoboWay</h2>
					This is just a prototype of a self balancing robot.\n
					So there are many little bugs in hardware and software.\n\n
					<b>As example:</b>
					<ul>
						<li>
							The mechanical characteristics of motors with a gear are not as good as they should be.\n
							I think this must be changed at first for newer versions
						</li>
						<li>
							The controller board could be much better.
							As example the ISP-Header and three potentiometers for the PID settings are missing
						</li>
						<li>
							The settings for the pid controller is not perfect
						</li>
					</ul>
					
					<p><br/></p>
					<p><br/></p>
					
					<h2>Source disclosure</h2>
					<ul>
						<li>
							http://www.rn-wissen.de/index.php/Regelungstechnik (09.03.2014)
						</li>
						<li>
							https://github.com/astromaf/VertiBOT/tree/master/Firmwares/PID_VertiBOT_V3_2 (09.03.2014)
						</li>
						<li>
							http://www.pieter-jan.com/node/11 (09.03.2014)
						</li>
						<li>
							AVR-Mikrocontroller-Kochbuch ( Entwurf und Programmierung praktischer Anwendungen ) - Franzis
						</li>
						<li>
							Powerprojekte mit Arduino und C - Franzis ( ISBN 978-3-645-65131-8 )
						</li>
						<li>
							Data sheet of gyroscope L3G4200D (rev. 3)
						</li>
						<li>
							Data sheet of accelerometer ADXL354 (Alaog Devices)
						</li>
						<li>
							http://www.ti.com/lit/ds/symlink/l293.pdf (09.03.2014)
						</li>
						<li>
							Data sheet of micro controller AtMega328P (Atmel rev. Rev. 8161D ? 10/09)
						</li>
						<li>
							Data sheet of sonar sensor SRF08
						</li>
					</ul>
					
					
					

*/
