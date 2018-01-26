/*
* CSCI213 Assignment 4
* --------------------------
* File name: ClientModule.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Code for the connection to the server
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 

public class ClientModule implements Runnable{
    
    private String ip ; 
    private int port; 
    private String loginName; 
    private Thread t; 
    private FPGClient c; 
    private ObjectOutputStream toSocket = null;
    private ObjectInputStream fromSocket = null; 
    
    private Deck d; 
    private ArrayList <Card> cardsOnTable ; 
    private ArrayList <Players> players ; 
    private int noOfPlayer;
    private boolean cont = true; 
    
    
    ClientModule (String ip, int port, String loginName, FPGClient client)
    {
        this.ip = ip; 
        this.port = port; 
        this.loginName = loginName; 
        c = client; 
        
        t = new Thread (this); 
        t.start();
    }
    
    public void run ()
    {
        InetAddress ina = null;
        
        try 
        {
            ina = InetAddress.getByName (ip);
        }
        catch (UnknownHostException e)
        {
            System.out.print ("Cannot find ip");
            System.exit (0);
        }
        
        Socket s = null; 
        
        try 
        {
            s = new Socket (ina, port); 
        }
        
        catch (IOException e)
        {
            System.out.println ("Cannot connect to host");
            System.exit (0); 
        }
        
        catch (Exception e)
        {
            
        }
        
        try 
        {
            toSocket = new ObjectOutputStream (s.getOutputStream ()); 
            fromSocket = new ObjectInputStream (s.getInputStream ()); 
        }
        
        catch (IOException e)
        {
            System.out.print("Cannot setup read write");
            System.exit(0);   
        }
        
        String input = loginName; 
	
        input = input.trim();       
        
        try 
        {
            toSocket.writeObject(input);
            toSocket.flush(); 
            toSocket.reset(); 

	} 
        catch (IOException io) 
        {
            System.out.print("Write to socket failed");
            System.exit(0);
        }  
        
        while (cont)
        {
            try
            {               
                Object response; 
                GameState gs; 
                Card card;
                Okay o; 
                Guess g; 
                
                response = fromSocket.readObject (); 
                
                if (response instanceof GameState)
                {
                    gs = (GameState) response;  
                    players = gs.getPlayers();
                    noOfPlayer = gs.getNoPlayer (); 
                    d = gs.getDeck (); 
                    cardsOnTable = gs.getCOT (); 
                    
                    c.startGame (players, noOfPlayer, d, cardsOnTable);
                }
                
                else if (response instanceof Card)
                {
                    card = (Card) response; 
                    c.showCard (card); 
                }
                
                else if (response instanceof Okay)
                {
                   o = (Okay) response; 
  
                   c.carryOn(); 
                }
                
                else if (response instanceof Guess)
                {
                   g = (Guess) response; 
  
                   Card Card1 = g.getCard1 (); 
                   Card Card2 = g.getCard2 (); 
                   
                   c.showCard (Card1); 
                   c.showCard (Card2); 
                }
                
                else if (response instanceof String)
                {
                    break;
                }
               
            }
            
            catch (ClassNotFoundException e)
            {
                System.out.println("Read or write to socket failed. Class Not Found");
                System.exit(0);
            }
            catch (IOException e)
            {
                System.out.println("Read or write to socket failed. ClientModule ioException");
                e.printStackTrace (); 
                System.exit(0);   
            }
        }
        
        try
        {
            fromSocket.close();      
            toSocket.close(); 
            s.close(); 
        }
        
        catch (IOException e)
        {
            e.printStackTrace(); 
        }
        
    }
    
    public void sendCard (Card c)
    {
        try 
        {
            toSocket.writeObject(c);
            toSocket.flush(); 
            toSocket.reset (); 

	} 
        catch (IOException io) 
        {
            System.out.print("Write to socket failed");
            System.exit(0);
        }  
    }
    
    public void addScore (String username) 
    {
        Winner w = new Winner (username); 
        
        try 
        {
            toSocket.writeObject(w);
            toSocket.flush(); 
            toSocket.reset (); 

	} 
        catch (IOException io) 
        {
            System.out.print("Write to socket failed");
            System.exit(0);
        }  
    }
    
    public void sendOkay () 
    {
        Okay o = new Okay ();
        try 
        {
            toSocket.writeObject(o);
            toSocket.flush(); 
            toSocket.reset (); 

	} 
        catch (IOException io) 
        {
            System.out.print("Write to socket failed");
            System.exit(0);
        }  
    }
    
    public void makeGuess (ArrayList <Card> cardsOnTable)
    {
        Guess g = new Guess (cardsOnTable);
        
        try 
        {
            toSocket.writeObject(g);
            toSocket.flush(); 
            toSocket.reset (); 

	} 
        catch (IOException io) 
        {
            System.out.print("Write to socket failed");
            System.exit(0);
        }  
    }
    
    public void sendEnd ()
    {
        String end = new String ("End");
        
        try 
        {
            toSocket.writeObject(end);
            toSocket.flush(); 
            toSocket.reset (); 

	} 
        catch (IOException io) 
        {
            System.out.print("Write to socket failed");
            System.exit(0);
        }  
        
        cont = false; 
        
    }
   
}
