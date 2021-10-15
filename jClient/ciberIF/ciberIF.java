/*
    This file is part of ciberRatoToolsSrc.

    Copyright (C) 2001-2008 Universidade de Aveiro

    ciberRatoToolsSrc is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ciberRatoToolsSrc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

package ciberIF;


import java.io.*;
import java.net.*;
import java.util.*;
import java.util.Vector;

import org.xml.sax.*;
import org.xml.sax.helpers.DefaultHandler;
import javax.xml.parsers.SAXParserFactory; 
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser; 


/** 
 *  models the result of a round of measures over all sensors
 */
class Measures {
	/** simulation cycle at time of measure */
	int     time;          // current cycle

	/** value measured from respective sensor */
	double  compass;  
	boolean compassReady;

	/** value measured from respective sensor */
	beaconMeasure [] beacon;
	/** only when beaconReady is true is the beacon measure significative */
	boolean       [] beaconReady;
	/** value measured from respective sensor */
	boolean collision; 
	boolean collisionReady;

	/** value measured from respective sensor */
	int     ground;
	boolean groundReady;

	/** array of measures from obstacle sensors */
	double  [] IRSensor;
	boolean [] IRSensorReady;

	/** value measured from respective led */
	boolean endLed, returningLed, visitingLed; 

	/** value measured from respective button */
	boolean startBut, stopBut; 

	/** value measured from GPS */
	gpsMeasure	gpsData;
        boolean         gpsReady;

        String []       hearMessage;
       

	/** Constructor */
	Measures(int nBeacons) {

		compassReady = collisionReady = groundReady = gpsReady = false;

		IRSensor = new double[4];
		IRSensorReady = new boolean [4];
		for(int i=0; i<4;i++) {
			IRSensorReady[i] = false;
		}


		beacon = new beaconMeasure [nBeacons];
		beaconReady = new boolean [nBeacons];

		for(int b=0; b<nBeacons;b++) {
			beacon[b]  = new beaconMeasure();
			beaconReady[b] = false;
		}

		gpsData = new gpsMeasure();

		hearMessage = new String [5];
	}
};

/** 
 *  the simulation parameter values
 */
class Parameters {
	int     simTime;  
	int     cycleTime;  
	double  beaconNoise;  
	double  obstacleNoise;  
	double  motorsNoise;  
	double  compassNoise;  
	int     keyTime;  
	int     nBeacons;  
};


/** 
 * parses a XML message of Sensors type and
 * gathers information in values property
*/
class SensorHandler extends DefaultHandler {

	public SensorHandler (int nBeac) {
		nBeacons = nBeac;
                activeTag = new String();
                hearFrom = 0;
	}
	/**
	 * values of all sensors are stored in this field
	 */
	private Measures values;
	private int      nBeacons;

        private String activeTag;
        private int    hearFrom;

	/**
	 * returns the Measures collected during parsing of message
	 */
	Measures getValues()
	{
		return values;
	}

	/** Main parsing method */
	public void startElement(String namespaceURI,
	                         String sName, // simple name
	                         String qName, // qualified name
	                         Attributes attrs)
	throws SAXException
	{
            activeTag = qName;
	    // Create values object to hold measures
	    if (values == null) values = new Measures(nBeacons);
	    
	    if(qName.equals("Measures")) {         // Measures Values

                 if (attrs != null) {

		      String timeStr=attrs.getValue("Time");         // Compass
	              if(timeStr!=null) {
		           values.time = Integer.valueOf(timeStr).intValue();
		      }

		 }
	    } else if(qName.equals("Sensors")) {   // Sensors Values
                 if (attrs != null) {

		      String compStr=attrs.getValue("Compass");         // Compass
	              if(compStr!=null) {
			   values.compassReady = true;
		           values.compass = Double.valueOf(compStr).doubleValue();
		      }

		      String groundStr=attrs.getValue("Ground");        //Ground
	              if(groundStr!=null) { 
			   values.groundReady = true;
			   values.ground = Integer.valueOf(groundStr).intValue();
		      }

		      String collisionStr=attrs.getValue("Collision");  // Collision
	              if(collisionStr!=null) {
			   values.collisionReady = true;
			   values.collision = collisionStr.equals("Yes");
		      }
                 }
	    }
	    else if(qName.equals("IRSensor")) {            // IRSensors

                 if (attrs != null) {

		      String idStr=attrs.getValue("Id");
	              if(idStr!=null) {
		           int IRid = Integer.valueOf(idStr).intValue();
		           String IRValStr=attrs.getValue("Value");
	                   if(IRValStr!=null) {
			       values.IRSensorReady[IRid] = true;
		               values.IRSensor[IRid] = Double.valueOf(IRValStr).doubleValue();
		           }
		      }
                 }
	    }
	    else if(qName.equals("BeaconSensor")) {            // BeaconSensor

                 if (attrs != null) {

		      String idStr=attrs.getValue("Id");
	              if(idStr!=null) {
		           int id = Integer.valueOf(idStr).intValue();
		           String valStr=attrs.getValue("Value");
	                   if(valStr!=null) {
			        values.beaconReady[id]=true;
		                if(!valStr.equals("NotVisible")) {
		                     values.beacon[id].beaconDir = Double.valueOf(valStr).doubleValue();
				     values.beacon[id].beaconVisible = true;
		                }
			        else {
				     values.beacon[id].beaconVisible = false;
			        }
		           }
		           else {
			        values.beaconReady[id]=false;
			        values.beacon[id].beaconVisible=false;
			        values.beacon[id].beaconDir=0.0;
		           }
		      }
                 }
	    }
	    else if(qName.equals("GPS")) {                // GPS

                 if (attrs != null) {

		      String xStr=attrs.getValue("X");             
	              if(xStr!=null) {
			    values.gpsData.x = Double.valueOf(xStr).doubleValue();
                            values.gpsReady = true;
		      }

		      String yStr=attrs.getValue("Y");             
	              if(yStr!=null) {
			    values.gpsData.y = Double.valueOf(yStr).doubleValue();
		      }

		      String dirStr=attrs.getValue("Dir");             
	              if(dirStr!=null) {
			    values.gpsData.dir = Double.valueOf(dirStr).doubleValue();
		      }

                 }
	    }
	    else if(qName.equals("Leds")) {                // Leds

                 if (attrs != null) {

		      String endLedStr=attrs.getValue("EndLed");              //EndLed
	              if(endLedStr!=null) {
			    values.endLed = endLedStr.equals("On");
		      }

		      String returningLedStr=attrs.getValue("ReturningLed");  //ReturningLed
	              if(returningLedStr!=null) {
			    values.returningLed = returningLedStr.equals("On");
		      }

		      String visitingLedStr=attrs.getValue("VisitingLed");  //VisitingLed
	              if(visitingLedStr!=null) {
			    values.visitingLed = visitingLedStr.equals("On");
		      }
                 }
	    }
	    else if(qName.equals("Buttons")) {          // Buttons

                 if (attrs != null) {

		      String startStr=attrs.getValue("Start");                //Start
	              if(startStr!=null) {
			    values.startBut = startStr.equals("On");
		      }

		      String stopStr=attrs.getValue("Stop");                  //Stop
	              if(stopStr!=null) {
			    values.stopBut = stopStr.equals("On");
		      }

                 }
	    }
	    else if(qName.equals("Message")) {          // Message
		      String fromStr=attrs.getValue("From");        //Ground
	              if(fromStr!=null) { 
			   hearFrom = Integer.valueOf(fromStr).intValue();
		      }
            }
	    else {
                //System.out.println("Unknown Tag:"+qName);
	    }
        } 

	public void endElement(String namespaceURI,
			        String sName, // simple name
			        String qName  // qualified name
						        )
	throws SAXException
	{
            activeTag="";
	} 

        public void characters(char[] ch,
                       int start,
                       int length)
       throws SAXException
       {
            if(activeTag.equals("Message")) {
                  if(values.hearMessage[hearFrom-1]==null)
                      values.hearMessage[hearFrom-1]=new String(ch,start,length);
                  else 
                      values.hearMessage[hearFrom-1]+=new String(ch,start,length);
            }
       }
};

/**
 *  class ReplyHandler parses a XML message of Reply type and
 *  gathers information in params property
 */
class ReplyHandler extends DefaultHandler {

	/**
	 * includes values of simulation parameters
	 * it is not constructed internally
	 */
	private Parameters params;

	/**
	 * returns the Parameters collected during parsing of message
	 */
	Parameters getParams()
	{
		return params;
	}

	public void startElement(String namespaceURI,
	                         String sName, // simple name
	                         String qName, // qualified name
	                         Attributes attrs)
	throws SAXException
	{
            
	    //Create params object to hold simulation parameters
	    if(params == null) params = new Parameters();

	    if(qName.equals("Reply")) {  // Reply Values

                 if (attrs != null) {

		      String statusStr=attrs.getValue("Status");         // Status
	              if(statusStr!=null) {
			   if( !statusStr.equals("Ok") ) {
                               System.out.println("Status: Refused");
			       System.exit(1);
			   }
			   else
                               System.out.println("Status: Ok");
		      }
                 }
	    }
	    if(qName.equals("Parameters")) {     // Parameters Values

                 if (attrs != null) {

		      String simTimeStr=attrs.getValue("SimTime");                 // SimTime
	              if(simTimeStr!=null) {
		          params.simTime = Integer.valueOf(simTimeStr).intValue();
		      }

		      String cycleTimeStr=attrs.getValue("CycleTime");             // CycleTime
	              if(cycleTimeStr!=null) {
		          params.cycleTime = Integer.valueOf(cycleTimeStr).intValue();
		      }

		      String compassNoiseStr=attrs.getValue("CompassNoise");       // CompassNoise
	              if(compassNoiseStr!=null) {
		          params.compassNoise = Double.valueOf(compassNoiseStr).doubleValue();
		      }

		      String beaconNoiseStr=attrs.getValue("BeaconNoise");         // BeaconNoise
	              if(beaconNoiseStr!=null) {
		          params.beaconNoise = Double.valueOf(beaconNoiseStr).doubleValue();
		      }

		      String obstacleNoiseStr=attrs.getValue("ObstacleNoise");     // ObstacleNoise
	              if(obstacleNoiseStr!=null) {
		          params.obstacleNoise = Double.valueOf(obstacleNoiseStr).doubleValue();
		      }

		      String motorsNoiseStr=attrs.getValue("MotorsNoise");         // MotorsNoise
	              if(motorsNoiseStr!=null) {
		          params.motorsNoise = Double.valueOf(motorsNoiseStr).doubleValue();
		      }

			      String keyTimeStr=attrs.getValue("KeyTime");   // KeyTime
	              if(keyTimeStr!=null) {
		          params.keyTime = Integer.valueOf(keyTimeStr).intValue();
		      }

		      String nBeaconsStr=attrs.getValue("NBeacons");               // NBeacons
	              if(nBeaconsStr!=null) {
		          params.nBeacons = Integer.valueOf(nBeaconsStr).intValue();
		      }

                 }
	    }
        } 

	public void endElement(String namespaceURI,
			        String sName, // simple name
			        String qName  // qualified name
						        )
	throws SAXException
	{
	} 
};

/**
 * class xmlParser creates the saxParser and parses
 * xmlMessages of types Sensors and Reply
 */
class xmlParser {

	/**
	 *   parses XML message using specified handler
	 *   @param buf     byte array containing message to be parsed
	 *   @param handler SAX event handler used to parse the message
	 */
    public void parse (byte[] buf, int length, DefaultHandler handler) {
        //Create factory
        SAXParserFactory factory = SAXParserFactory.newInstance();
        try {

            //replace null character (if it exists)
            if(buf[buf.length-1] == '\0') 
                buf[buf.length-1] = ' ';

            //Create parser
            SAXParser saxParser = factory.newSAXParser();

            // ConvertString to ByteArrayInputStream
            ByteArrayInputStream bstream=new ByteArrayInputStream(buf,0,length);

            // Parse ByteArrayInputStream
            saxParser.parse( bstream, handler ); 
        } 

        catch (SAXParseException spe) {
            // Error generated by the parser
            System.out.println("\n** Parsing error" 
                    + ", line " + spe.getLineNumber()
                    + ", uri " + spe.getSystemId());
            System.out.println("   " + spe.getMessage() );

        } 
        catch (Throwable t) {
            t.printStackTrace();
        }
    }

};


/**
 * provides the interface with the simulator,
 * all types of communication with the simulator may be realized using methods of this class
 */
public class ciberIF {


    /** 
     * ciberIF contructor
    *  The constructor inits all necessary data structures,
    */
    public ciberIF() {

        // Get a datagram socket
	try {
                socket = new DatagramSocket();
	}
	catch(Exception e) {
	        e.printStackTrace();
	}

	
    
	// Create Parser
	parser = new xmlParser();
    }

    /**
     * Initializes Robot and Connects to Simulator
     * @param name        robot name
     * @param pos         initial position of robot in initial grid
     * @param hostname    host where simulator running
     */
    public boolean InitRobot(String name, int pos, String hostname)
    {
        //// Send init message
	// Construct message
        sendInitAndParseReply(hostname, new String("<Robot Id=\"" + pos + "\""+
			              " Name=\"" + name + "\"/>"));

	return true;
    }

    /**
     * Initializes Robot and Connects to Simulator, allows specification
     * of obstacle sensors position
     * @param name        robot name
     * @param pos         initial position of robot in initial grid
     * @param IRSensorAngles  array of doubles that specifies position of IR sensors,
     *                    positions are given from angle (in degrees) from front of Robot
     * @param hostname    host where simulator running
     */
    public boolean InitRobot2(String name, int pos, double IRSensorAngles[], String hostname)
    {
        //// Send init message
	// Construct message
        String strInit = new String("<Robot Id=\"" + pos + "\"" +
			                " Name=\"" + name +"\" >");

	for(int i = 0; i < IRSensorAngles.length; i++) {
             strInit += " " + " <IRSensor Id=\"" + i + "\" " +
		                         "Angle=\"" + IRSensorAngles[i] + "\" /> ";
	}

	strInit += "</Robot>";
	
	sendInitAndParseReply(hostname, strInit);

	return true;
    }

    /**
     * Read a message from simulator. 
     * If no message is available wait, when message arrives parses it.
     * This is the main synchronization method of this library.
     */
    public void ReadSensors() {

        byte[] bufread = new byte[4096];
        DatagramPacket packet = new DatagramPacket(bufread, bufread.length);

	// read socket
	try {
            socket.receive(packet);
	}
	catch(Exception e) {
		e.printStackTrace();
	}


	// parse message
	SensorHandler sensHandler = new SensorHandler(params.nBeacons);
	parser.parse(packet.getData(),packet.getLength()-1, sensHandler);
	values = sensHandler.getValues();
    }

    /**
     * get simulation time of last received message
     */
    public double GetTime() {
	    return values.time;
    }

    /**
     * Indicates if a new Obstacle measure from sensor id has arrived.\
     * The value of GetObstacleSensor is invalid when IsObstacleReady returns false
     */
    public boolean IsObstacleReady(int id) {
	    return values.IRSensorReady[id];
    }

    /**
     * get obstacle sensor measure, value is inversely proportional to nearest obstacle distance
     */
    public double GetObstacleSensor(int id) {
	    return values.IRSensor[id];
    }

    /**
     * only when IsBeaconReady returns true is the beacon measure significative
     */
    public boolean IsBeaconReady(int id) {
	    return values.beaconReady[id];
    }

    /**
     * get beacon sensor measure, value is the direction of beacon in robot coordinates (-180.0,180.0)
     */
    public beaconMeasure GetBeaconSensor(int id) {
	    return values.beacon[id];
    }

    /**
     * only when IsCompassReady returns true is the compass measure significative
     */
    public boolean IsCompassReady() {
	    return values.compassReady;
    }

    /**
     * get compass sensor measure, value is the direction of robot in ground coordinates (-180.0,180.0)
     */
    public double GetCompassSensor() {
	    return values.compass;
    }

    /**
     * only when IsGroundReady returns true is the ground measure significative
     */
    public boolean IsGroundReady() {
	    return values.groundReady;
    }

    /**
     * get ground sensor measure, active when in target area
     */
    public int GetGroundSensor() {
	    return values.ground;
    }

    /**
     * only when IsBumperReady returns true is the bumper measure significative
     */
    public boolean IsBumperReady() {
	    return values.collisionReady;
    }

    /**
     * only when IsBumperReady returns true is the bumper measure significative
     */
    public boolean NewMessageFrom(int id) {
            if( values.hearMessage[id-1]==null) return false;
	    return !values.hearMessage[id-1].equals("");
    }

    /**
     * get bumper sensor measure, active when robot collides
     */
    public boolean GetBumperSensor() {
	    return values.collision;
    }

    /**
     * get bumper sensor measure, active when robot collides
     */
    public String GetMessageFrom(int id) {
	    return values.hearMessage[id-1];
    }

    /**
     * only when IsGPSReady returns true are the GPS measures (X, Y, Dir) significative
     */
    public boolean IsGPSReady() {
	    return values.gpsReady;
    }

    /**
     * get x coordinate of current position from GPS sensor, 
     * can be used for debug, invoke simulator with '-gps' option
     */
    public double GetX() {
	    return values.gpsData.x;
    }

    /**
     * get y coordinate of current position from GPS sensor, 
     * can be used for debug, invoke simulator with '-gps' option
     */
    public double GetY() {
	    return values.gpsData.y;
    }

    /**
     * get robot orientation of current position from GPS sensor, 
     * can be used for debug, invoke simulator with '-gps' option
     */
    public double GetDir() {
	    return values.gpsData.dir;
    }

    public void RequestCompassSensor() {
	    send(new String("<Actions> <SensorRequests Compass=\"Yes\"/> </Actions>"));
    }

    public void RequestGroundSensor() {
	    send(new String("<Actions> <SensorRequests Ground=\"Yes\"/> </Actions>"));
    }

    public void RequestIRSensor(int id) {
	    send(new String("<Actions> <SensorRequests IRSensor" + id + "=\"Yes\"/> </Actions>"));
    }

    public void RequestBeaconSensor(int id) {
	    send(new String("<Actions> <SensorRequests Beacon" + id + "=\"Yes\"/> </Actions>"));
    }

    public void RequestSensors(String [] sensorIds) {
	    String msg = new String("<Actions> <SensorRequests ");

	    for (int s=0; s < sensorIds.length ; s++) {
	       msg += ( sensorIds + "=\"Yes\" ");
	    }

            msg += "\"/> </Actions>";

	    send(msg);
    }

    /**
     * get start button state
     */
    public boolean GetStartButton() {
	    return values.startBut;
    }

    /**
     * get stop button state
     */
    public boolean GetStopButton() {
	    return values.stopBut;
    }

    /**
     * get returning led state, usefull to verify if SetReturningLed() was executed in the simulator
     */
    public boolean GetVisitingLed() {
	    return values.visitingLed;
    }

    /**
     * get returning led state, usefull to verify if SetReturningLed() was executed in the simulator
     */
    public boolean GetReturningLed() {
	    return values.returningLed;
    }

    /**
     * get end led state, usefull to verify if Finished() was executed in the simulator
     */
    public boolean GetFinished() {
	    return values.endLed;
    }

    /**
     * drive left motor with lPow and right motor with rPow,
     * powers are in (-0.15, 0.15)
     */
    public void DriveMotors(double lPow, double rPow)
    {
	    send(new String("<Actions LeftMotor=\"" + lPow + "\" RightMotor=\"" + rPow + "\"/>"));
    }

    /**
     * broadcast message to all other robots,
     * the maximum size is limited
     */
    public void Say(String msg)
    {
	    send(new String("<Actions><Say><![CDATA[" + msg + "]]></Say></Actions>"));
    }

    /**
     * signal the end of phase 1 (go to target)
     */
    public void SetReturningLed(boolean val)
    {
	    send(new String("<Actions LeftMotor=\"0\" RightMotor=\"0\" ReturningLed=\"" + (val?"On":"Off") + "\"/>"));
    }

    public void SetVisitingLed(boolean val)
    {
	    send(new String("<Actions LeftMotor=\"0\" RightMotor=\"0\" VisitingLed=\"" + (val?"On":"Off") + "\"/>"));
    }

    /**
     * finish the round
     */
    public void Finish()
    {
	    send(new String("<Actions LeftMotor=\"0\" RightMotor=\"0\" EndLed=\"On\"/>"));
    }

    /** read parameter settings */
    public int GetCycleTime() {
	    return params.cycleTime;
    }

    /** read parameter settings */
    public int GetFinalTime() {
	    return params.simTime;
    }

    /** read parameter settings */
    public int GetKeyTime() {
	    return params.keyTime;
    }

    /** read parameter settings */
    public double GetNoiseObstacleSensor() {
	    return params.obstacleNoise;
    }

    /** read parameter settings */
    public double GetNoiseBeaconSensor() {
	    return params.beaconNoise;
    }

    /** read parameter settings */
    public double GetNoiseCompassSensor() {
	    return params.compassNoise;
    }

    /** read parameter settings */
    public double GetNoiseMotors() {
	    return params.motorsNoise;
    }

    /** read parameter settings */
    public int GetNumberOfBeacons() {
	    return params.nBeacons;
    }


    // private

    private void sendInitAndParseReply(String hostname, String strInit)
    {
	port = 6000;
        byte[] buf = strInit.getBytes();

	// parse hostname if it is in "host:port" format
	int pdiv = hostname.indexOf(":");
        if(pdiv != -1) {
		port = Integer.valueOf(hostname.substring(pdiv+1)).intValue();
		hostname = hostname.substring(0,pdiv);
	}

	//System.out.println("host = \""+ hostname + "\" port = " + port);

        // Get the simulator host address 
    	try {
                address = InetAddress.getByName(hostname);
    	}
    	catch(Exception e) {
		e.printStackTrace();
	}

	// Insert message in a DatagramPacket and send
        DatagramPacket packet = new DatagramPacket(buf, buf.length, address, port);
	try {
            socket.send(packet);
	}
	catch(Exception e) {
		e.printStackTrace();
	}
    
        //// Get response
	//  Create buffer and DatagramPacket
        byte[] bufread = new byte[1024];
        packet = new DatagramPacket(bufread, bufread.length);
	//  Read socket
	try {
            socket.receive(packet);
	}
	catch(Exception e) {
		e.printStackTrace();
	}

	// parse init response  
	ReplyHandler replyHandler = new ReplyHandler();
	parser.parse(packet.getData(), packet.getLength()-1, replyHandler);
	params = replyHandler.getParams();

	// port of incoming sucessful reply is the destination of all subsequent messages
        port = packet.getPort();
    }


    // Send a message to simulator
    private void send(String msg) {
	byte[] buf = new byte[1024];

	buf = msg.getBytes();

	DatagramPacket packet =  new DatagramPacket(buf,buf.length,address,port);
	try {
           socket.send(packet);
	}
	catch(Exception e) {
		e.printStackTrace();
	}
    }

    private DatagramSocket socket;
    private InetAddress address;
    private xmlParser parser;
    private int port;

    private Measures values;  // holds all measures present in the last received message
    private Parameters params;  // holds all measures present in the last received message

};
