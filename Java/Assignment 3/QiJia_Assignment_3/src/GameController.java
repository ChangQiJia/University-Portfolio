/*
* CSCI213 Assignment 3
* --------------------------
* File name: GameController.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: The Main Engine of the Game
*/

import java.util.*;
import javax.swing.*;
import java.awt.*; 

public class GameController {

	private GameView view;
	private Dealer dealer;
	private ArrayList<GamePlayerInterface> players;
        private ViewController viewCon; 
        private boolean emptyTable = false; 


        
       public GameController(ViewController viewController, Dealer dealer,
			ArrayList<GamePlayerInterface> players) {
		this.viewCon = viewController;
		this.dealer = dealer;
		this.players = players;
	}
       
        public void addGV (GameView gv)
       {
            this.view = gv; 
            view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
       }
        
        public void newGame() 
        {
            view.setVisible (false); 
            
            this.view = new GameView (viewCon, this, players); 
            view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
            run(); 
        }
        
	public void run() {
		view.showView(); 
                
	}
        
        public void playerTurn (GamePlayerInterface player)
        {
            if(view.getNumberOfCardsOnTable()==0){
                    view.printMessage("Game end");
                    view.gameEnd(); 
		}
            
            else
                view.showFaceDownCards();
						
        }
        
        public void cardSelected (ArrayList <Card> cards, GamePlayerInterface player)
        { 
            Card card1 = cards.remove (0); 
            Card card2 = cards.remove (0); 
           
            if (card1.getName().equals(card2.getName())) {
                
		view.printMessage(player.getLoginName() + " got a match! \nDealer replacing two cards");
		
                player.addScore(); 
		
		if(view.getNumberOfCards()!=0){
                    view.replaceCardAt(card1);
                    
                    if(view.getNumberOfCards()!=0){
                        view.replaceCardAt(card2);
                    }
                    
                    else
                        view.removeCard (card2); 
		}
                
                else
                {
                    view.removeCard (card2); 
                    view.removeCard (card1); 
                }

            } 
            
            else {
                    view.printMessage( player.getLoginName() + " did not have a match!");
                 }
            
            view.resetTurn(); 
        }
        
        public void emptyTable ()
        {
            emptyTable = true; 
        }
        
        public void compareScore()
        {
            int highest = 0; 
            int counter = 0; 
            ArrayList <String> name = new ArrayList <> (); 
            String toPrint = ""; 
            GamePlayerInterface winner = null; 
 
            
            for (GamePlayerInterface p : players)
            {
                if (highest < p.getScore())
                    highest = p.getScore(); 
            }
            
            for (GamePlayerInterface p : players)
            {
                if (highest == p.getScore())
                    counter++;
            }
            
            for (GamePlayerInterface p: players)
            {
                if (highest == p.getScore())
                   name.add(p.getLoginName());          
            }
            
            if (counter == 1)
            {
                view.printFinalMessage (name.get(0) + " won! Score: " + highest);
                
                for (GamePlayerInterface p: players)
                {
                    if (highest == p.getScore())
                       winner = p;          
                }
                if (!(winner instanceof ComputerPlayer))
                    viewCon.addScore (winner.getLoginName(), 1);
            }
            else
            {
                for (String n: name)
                    toPrint = toPrint + " , " + n;
            
                    view.printFinalMessage (toPrint + " has tied! Score: " + highest);
            }
            
            name.clear(); 
        }
        
        public void getScore (ArrayList <Integer> scoreOfPlayer) 
        {
            for (GamePlayerInterface p : players)
            {
                scoreOfPlayer.add (p.getScore());
            }
        }
        
        public void nextMove (GamePlayerInterface p) 
        {
            if (p instanceof ComputerPlayer )
                view.makeNextMove(); 
        }

}
