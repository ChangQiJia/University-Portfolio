/*
* CSCI213 Assignment 3
* --------------------------
* File name: GameModule.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Set up the players before game starts
*/

import java.util.*;

public class GameModule {
    
        private GameController gameController; 
        private ViewController viewController; 
        private ArrayList<GamePlayerInterface> players; 
    
        public GameModule ()
        {
           
        }
        public void start () 
        {
            viewController = new ViewController(players, this);
            viewController.run () ; 
        }
	public void run(String username, String password, int score){
		
		ComputerPlayer computerPlayer1 = new ComputerPlayer("Computer Player1","",0,new Brain());
		GamePlayer humanPlayer = new GamePlayer (username, password, score);
		
		
		Dealer dealer = new Dealer(new Brain());
			
		players = new ArrayList<GamePlayerInterface>();
		players.add(humanPlayer);
		players.add(computerPlayer1);
		
                
		viewController.updatePlayers (players);
                
		gameController = new GameController(viewController,dealer,players);
                
                viewController.addGC (gameController); 
                gameController.addGV(viewController.getGameView()); 
	
		viewController.run();
	
	}
	
	
}
