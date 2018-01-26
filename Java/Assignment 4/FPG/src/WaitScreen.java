/*
* CSCI213 Assignment 4
* --------------------------
* File name: WaitScreen.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Code for Server when waiting for connection
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class WaitScreen implements Runnable{

    private int portNum; 
    private int noOfPlayer; 
    private Thread t; 
    private FPGServer s;
    private BroadCaster bc; 
    
   WaitScreen (int portNum, int noOfPlayer, FPGServer s, BroadCaster bc)
    {
        this.portNum = portNum; 
        this.noOfPlayer = noOfPlayer; 
        this.s = s; 
        this.bc = bc; 
        
        t = new Thread (this); 
        t.start();
        
    }
   
   public void run()
   {
        ServerSocket serverSocket = null; 
        
        try 
        {
            serverSocket = new ServerSocket (portNum);
        }
        
        catch (IOException e)
        {
            System.out.println ("Port " + portNum +" not avaliable");
            System.exit (0); 
        }
        
        for (int i = 1 ; i <= noOfPlayer; i++)
        {
            Socket clientSocket = null; 

            try 
            {
                System.out.println ("Waiting for client connection");
                clientSocket = serverSocket.accept(); 
                System.out.println ("Client connected");
            }

            catch (IOException e)
            {
                System.out.println ("Client unable to connect");
                System.exit (0); 
            }
              
            ClientHandler c = new ClientHandler (clientSocket, i, s, bc); 
            System.out.println ("Client " + i + " thread created");   
            bc.addClient (c); 

        } 
    }
   
   public void addToBc (String username, int i)
   {
       HumanPlayer player = new HumanPlayer (username, i); 
       
       bc.addPlayer (player); 
   }
   
}
