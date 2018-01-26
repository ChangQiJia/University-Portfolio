/*
* CSCI213 Assignment 4
* --------------------------
* File name: BraodCaster.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: In charge of sending information to all the clients
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class BroadCaster implements Serializable{
    
    private ArrayList <Players> players ; 
    private int noOfPlayers;
    private ArrayList <ClientHandler> clients = new ArrayList <> ();
    private ArrayList <Socket> sock = new ArrayList <> (); 
    private GameState gs;
    private ObjectOutputStream out; 
    private ObjectInputStream in; 
    
    BroadCaster (int noOfPlayers)
    {
        this.noOfPlayers = noOfPlayers; 
        players = new ArrayList <> (); 
    }
    
    public synchronized void addPlayer (Players p)
    {
        players.add (p);
        
        checkStart();
    }
    
    public void addClient (ClientHandler c)
    {
        clients.add (c); 
    }
    
    public void checkStart () 
    {   
        if (players.size() == noOfPlayers)
        {
            ComputerPlayer c = new ComputerPlayer ("Dealer", (noOfPlayers+1));
            players.add (c); 
            
            startGame();
        }
    }
    
    public void startGame ()
    {
        gs = new GameState (players, players.size());
        
        for (ClientHandler c: clients)
        {
            c.startGame (gs, players);          
        }
        
    }
    
    public void addSocket (Socket s)
    {
        sock.add (s); 

    }
    
    public void showCard (Card c)
    {
        for (ClientHandler cl: clients)
        {
           cl.showCard (c);          
        }
    }
    
    public void setWinner (Winner w)
    {
        gs.setWinner (w); 
        
        for (ClientHandler cl: clients)
        {
           cl.sendEnd ();          
        }
    }
    
    public void sendOkay ()
    {
        for (ClientHandler cl: clients)
        {
           cl.sendOkay ();          
        }
    }
    
    public void makeGuess (Guess g)
    {
        ArrayList <Card> cot = g.getCOT(); 
        
        int rand1 , rand2; 
        Random r = new Random (); 
        Card temp1, temp2; 
        
        rand1 = r.nextInt(cot.size());
        
        do
        {
            rand2 = r.nextInt (cot.size()); 
        } while (rand2 == rand1);        
        
        temp1 = cot.get (rand1);
        temp2 = cot.get (rand2); 
        
        g.setCard1 (temp1); 
        g.setCard2 (temp2); 
        
        for (ClientHandler cl: clients)
        {
           cl.sendGuess (g);          
        }
    }
    
    public void sendEnd () 
    {
        for (ClientHandler cl: clients)
        {
           cl.sendEnd ();          
        }
    }
   
}
