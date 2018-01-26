/*
* CSCI213 Assignment 3
* --------------------------
* File name: ViewController.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: Controls the GUI
*/

import java.util.*; 

public class ViewController {
    
    private GameController gameController;
    private LoginView loginView; 
    private GameView gameView; 
    private ArrayList<GamePlayerInterface> players;
    private Admin a = new Admin (); 
    private GameModule gm;
    
    ViewController (ArrayList<GamePlayerInterface> players, GameModule gm)
    {
        loginView = new LoginView (this);      
        this.players = players; 
        this.gm = gm; 
    }
   
    public void showLoginView () 
    {
        loginView.setVisible (true); 
    }
    
    public void showGameView()
    {
        loginView.setVisible (false); 
        gameController.run(); 
        
    }
    
    public void run () 
    {
        loginView.setVisible (true); 
    }
    
    public void addGC (GameController gc)
    {
        this.gameController = gc; 
        
        gameView = new GameView (this, gameController, players); 
    }
    
    public void loginCallback (String username, String password) 
    {
        boolean loggedIn = false; 
        String date; 
        
        loggedIn = a.checkLogin(username, password);
        loginView.setVisible (false);
        
        String pass = a.getUserPass (username); 
        int score = a.getUserScore (username);
        
        if (loggedIn == true)
        {
            date = a.getDate(); 

            showWelcomeMessage(date, username); 
           
            gm.run (username, pass, score);
            loginView.setVisible (false); 
        } 
        
        else 
        {
            loginView.setVisible (false); 
            loginView.tryAgain(); 
        }   
    }
    
    public void updatePlayers (ArrayList <GamePlayerInterface> players)
    {
        this.players = players; 
    }
    
    public GameView getGameView ()
    {
        return gameView; 
    }
    
    public void welcomeMessageCallBack ()
    {
       showGameView(); 
    }
    public void showWelcomeMessage (String date, String username)
    {
       int oldYear, oldMonth, oldDays;
       int newYear, newMonth, newDays; 
       int year, month, days;
       
       String temp; 
       String [] dummy = new String [10];
       String [] whiteSpace = new String [10];
       
       temp = a.getDate(); 
       
       whiteSpace = temp.split ("\\s+");    
       dummy = whiteSpace[1].split ("-");
       
      
       newDays = Integer.parseInt(dummy[2]); 
       newMonth = Integer.parseInt(dummy[1]);
       newYear = Integer.parseInt(dummy[0]);
       
       temp = a.getOldDate(username); 
              
       whiteSpace = temp.split ("\\s+");
       
       dummy = whiteSpace[1].split ("-");
       
       oldDays = Integer.parseInt(dummy[2]);
       oldMonth = Integer.parseInt(dummy[1]);
       oldYear = Integer.parseInt(dummy[0]);
       
       days = newDays - oldDays; 
       month = newMonth - oldMonth; 
       year = newYear - oldYear; 
       
       if (days < 0)
       {
           month --;
           days += 30;
       }
       
       if (month < 0)
       {
           year --;
           month += 12;
       }
       
       temp = ("Welcome back " + username + " we have missed you for ");
       
       if (year > 0)
        {
            temp = temp + (year + " year ");
        }
       if (month > 0)
       {
           temp = temp + (month + " month and ");
       }
       
        temp = temp + (days + " days!\n");
        
        loginView.printMessage (temp); 
    }
    
    public void addScore (String username, int i)
    {
        a.updateScore (username, i);
    }
    
    public void tryAgainCallBack ()
    {
        showLoginView(); 
    }
}
