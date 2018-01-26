/*
* CSCI213 Assignment 4
* --------------------------
* File name: ClientHandler.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Thread to server each client
*/

import java.net.*;
import java.io.*;
import java.util.*; 


public class ClientHandler extends Thread implements Serializable{
    
    private Socket clientSocket; 
    private int serverCounter; 
    private Thread t; 
    private FPGServer server; 
    private String username; 
    private BroadCaster bc; 
    private ArrayList <Players> players; 
    private ObjectOutputStream out; 
    private ObjectInputStream in; 
    private int score = 0; 
    private GameState gs; 
    private int okayCounter = 0; 
    private boolean cont = true; 
    private static int counter = 0; 
    
    ClientHandler (Socket s, int serverCounter, FPGServer server, BroadCaster bc)
    {
        this.clientSocket = s ; 
        this.serverCounter = serverCounter; 
        this.server = server;
        this.bc = bc; 
        
        bc.addSocket (s); 
        
        try
            {
                out = new ObjectOutputStream (clientSocket.getOutputStream()); 
                in = new ObjectInputStream (clientSocket.getInputStream()); 
            }
        catch (IOException e)
            {
                System.out.println("Write to socket failed.");
                System.exit (0);
            }
        
        t = new Thread (this); 
        t.start();
    }
    
    public void run () 
    {
        while (cont)
        {
            try
            {               
                Object response; 
                
                response = in.readObject (); 
                
                if (response instanceof String)
                {
                    String input = (String) response;  
                    
                    if (input.equals ("End"))
                    {
                        
                    }
                    
                    else
                    {
                        server.updateScreen (input, serverCounter);
                        username = input; 
                    }
                }
                
                if (response instanceof Card)
                {
                    Card c = (Card) response; 

                    bc.showCard (c);
                }
                
                if (response instanceof Winner)
                {
                    Winner w = (Winner) response; 
                    
                    if (counter == 0)
                        bc.setWinner (w); 
                    
                    counter++; 

                }
                
                if (response instanceof Okay)
                {
                   
                    Okay o = (Okay) response;
                    
                    bc.sendOkay();  
                    
                }
                
                if (response instanceof Guess)
                {
                    Guess g = (Guess) response; 
                    
                    bc.makeGuess(g); 
                }
                
               
            }
            
            catch (ClassNotFoundException e)
            {
                System.out.println("Read or write to socket failed. ClientHandler Class Not Found");
                System.exit(0);
            }
            catch (IOException e)
            {
                System.exit(0);   
            }
        }
        
        try 
        {
            in.close(); 
            out.close(); 
            clientSocket.close(); 
        }
        
        catch (IOException e)
        {
            System.exit (0);
        }
    }
    
    public void startGame (GameState gs, ArrayList<Players> players)
    {
        this.players = players; 
        
       	try 
            {
		out.writeObject(gs);
		out.flush();
                out.reset();
            } 
        catch (IOException e) 
            {
		System.exit (0);
            }
            
        
    }
    
    public void showGame (GameState gs)
    {
       	try 
            {
		out.writeObject(gs);
		out.flush();
                out.reset();
            } 
        catch (IOException e) 
            {
		System.exit (0);
            }
                
    }
        
    
    public String getLoginName () 
    {
        return username; 
    }
    
        public int getScore ()
    {
        return score; 
    }
    
    public void addScore ()
    {
        score++;
    }
    
    public void setScore (int s)
    {
        score = s; 
    }
    
    public void showCard (Card c)
    {
        try 
            {
		out.writeObject(c);
		out.flush();
                out.reset();
            } 
        catch (IOException e) 
            {
		System.exit (0);
            }
    }
    
    public void sendOkay ()
    {      
        Okay o = new Okay (); 
        try 
            {
		out.writeObject(o);
		out.flush();
                out.reset();
            } 
        catch (IOException e) 
            {
		System.exit (0);
            }
    }
    
    public void sendGuess (Guess g)
    {
        try 
            {
		out.writeObject(g);
		out.flush();
                out.reset();
            } 
        catch (IOException e) 
            {
		System.exit (0);
            }
    }
    
    public void sendEnd ()
    {
        try 
            {
		out.writeObject("End");
		out.flush();
                out.reset();
            } 
        catch (IOException e) 
            {
                System.exit (0);
            }
        
        cont = false; 
        
    }
}
