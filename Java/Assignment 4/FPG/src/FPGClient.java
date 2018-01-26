/*
* CSCI213 Assignment 4
* --------------------------
* File name: FPGClient.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: GUI for the client
*/

import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.swing.*; 
import java.awt.event.*; 
import java.awt.*; 
import javax.sound.sampled.*;

public class FPGClient implements Serializable{
    
    private JFrame frame; 
    private JTextField loginTF; 
    private JPasswordField passPF; 
    private JTextField ipTF; 
    private JTextField portTF;
    private Admin a = new Admin (); 
    private String loginName;
    private String password;
    private ClientModule cm; 
    
    private Deck d; 
    private ArrayList <Card> cardsOnTable ; 
    private ArrayList <Players> players ; 
    private int noOfPlayer;
    private ArrayList <Card> pickedCards = new ArrayList <> (); 
    
    private JPanel cardPanel = new JPanel (); 
    private Point click; 
    private int turns = 0; 
    private int playerTurn = 0; 
    private javax.swing.Timer time; 
    private JFrame messageFrame; 
    
    public static void main (String [] args) {
        new FPGClient().run(); 
    }
    
    public void run () 
    {
        frame = new JFrame ("Game Login");
        frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel (); 
        panel.setPreferredSize (new Dimension (300,175));
        
        JLabel loginName = new JLabel ("Login Name");
        loginName.setPreferredSize (new Dimension (75,20));
        loginTF = new JTextField (15);
        
        JLabel password = new JLabel ("Password");
        password.setPreferredSize (new Dimension (75,20));
        passPF = new JPasswordField (15);
        
        JLabel IP = new JLabel ("IP");
        IP.setPreferredSize (new Dimension (75,20));
        ipTF = new JTextField (15);
        
        JLabel port = new JLabel ("Port");
        port.setPreferredSize (new Dimension (75,20));
        portTF = new JTextField (15);
        
        JButton login = new JButton ("Login");
        login.addActionListener (new LoginButtonListener ());
              
        panel.add (loginName); 
        panel.add (loginTF); 
        panel.add (password); 
        panel.add (passPF); 
        panel.add (IP); 
        panel.add (ipTF); 
        panel.add (port); 
        panel.add (portTF); 
        panel.add (login); 
        
        frame.add (panel); 
        frame.pack(); 
        frame.setVisible (true); 
        
        
    }
    
    private class LoginButtonListener implements ActionListener 
    {
        public void actionPerformed (ActionEvent e)
        {
            loginName = loginTF.getText(); 
            password = new String (passPF.getPassword()); 
            
            String IP = ipTF.getText(); 
            String port = portTF.getText(); 
            
            int portNo = Integer.parseInt (port); 
            
            frame.setVisible (false); 
            loginButtonCallBack (IP, portNo);
            
        }
    }
    
    public void loginButtonCallBack (String ip, int port)
    {
        if (!userLogin())
        {       
            System.out.println ("Fail to login!");
            System.exit (0); 
        }
        a.updateDate(loginName);
        
        cm = new ClientModule (ip, port, loginName, this);
        
        showWait (); 
           
    }
    
    public boolean userLogin () 
    {
        boolean success = false; 
        
        success = a.checkLogin (loginName, password);   
        
        return success; 
    }
    
    public void showWait () 
    {
       frame = new JFrame ("Game");
       frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE); 
       
       JPanel panel = new JPanel (); 
       
       JLabel wait = new JLabel ("Waiting for more players to connect");
       
       panel.add (wait); 
       
       frame.add (panel); 
       frame.setPreferredSize (new Dimension (400,75));
       frame.pack(); 
       frame.setVisible (true); 
    }
    
    public String getLoginName ()
    {
        return loginName; 
    }
    
    public void startGame (ArrayList <Players> player, int noOfPlayer, Deck d, ArrayList <Card> cardsOnTable )
    {
        this.players = player;
        this.noOfPlayer = noOfPlayer; 
        this.d = d; 
        this.cardsOnTable = cardsOnTable;
        
        frame.setVisible (false); 
        frame.dispose ();
        
        showScreen ();
    }
    
    public void showScreen () 
    {
        frame = new JFrame ("Game " + loginName);
        frame.setDefaultCloseOperation (JFrame.EXIT_ON_CLOSE); 
        
        JLabel currentScore;
        JPanel playerInfo = new JPanel();
        playerInfo.setPreferredSize (new Dimension (200,90));
            
        JPanel cardDeck = new JPanel();
        cardDeck.setPreferredSize (new Dimension (200,400));
        JLabel deckPic = new JLabel ();
        JLabel noOfCard = new JLabel ("No of Cards: "+ d.getNumberOfCards());
        deckPic.setIcon (new ImageIcon ("cardDeck.png"));
        cardDeck.add (deckPic);
        cardDeck.add (noOfCard); 
        
        for (Players p: players)
            {
                currentScore = new JLabel (p.getLoginName() + " : " + p.getScore());
                currentScore.setPreferredSize (new Dimension (200, 20));
                playerInfo.add (currentScore); 
            } 
        
        cardPanel.add (playerInfo);
        cardPanel.add (cardDeck); 
            
            for (Card cards : cardsOnTable)
            { 
                cards.addMouseListener (new MListener());
                cardPanel.add (cards); 
            }
           
        frame.add (cardPanel); 
        frame.pack();     
        frame.setPreferredSize (new Dimension (1600,500)); 
        
        frame.setVisible (true); 
    }
    
    private class MListener implements MouseListener{
                        
            public void mouseClicked (MouseEvent event)
            {
                click = new Point (event.getPoint ());
                Object temp = event.getSource (); 
                Card c = (Card) temp;
                
                if (c.active ())
                    cm.sendCard (c);
            }
            
            public void mousePressed(MouseEvent me) {
                
            }

        
            public void mouseReleased(MouseEvent me) {
                
            }


            public void mouseEntered(MouseEvent me) {
    
           }


            public void mouseExited(MouseEvent me) {
            
            }
        }
    
    private class TimerListener implements ActionListener
        {
            public void actionPerformed (ActionEvent e)
            {         
                cardSelected (pickedCards, playerTurn); 
                
                time.stop();
            } 
        }
    
    public void showCard (Card newCard) 
    {   
        
        for (Card c: cardsOnTable)
        {
            if (c.getName().equals (newCard.getName()))
            {
                if (c.getSuit().equals (newCard.getSuit()))
                {
                    flipCard (c); 
                }
            }
            
        }
        
    }
    
    public void flipCard (Card c)
    {
        String name = c.getName(); 
        String suit = c.getSuit(); 
        
        
        if (suit.equals("Diamond"))
        {
            if (name.equals ("Ace"))
                c.changeImage ("AceDiamond.png");
            else if (name.equals ("Jack"))
                c.changeImage ("JackDiamond.png");
            else if (name.equals ("King"))
                c.changeImage ("KingDiamond.png");
            else
                c.changeImage ("QueenDiamond.png");
        }
        
        else
         {
            if (name.equals ("Ace"))
                c.changeImage ("AceHearts.png");
            else if (name.equals ("Jack"))
                c.changeImage ("JackHearts.png");
            else if (name.equals ("King"))
                c.changeImage ("KingHearts.png");
            else
                c.changeImage ("QueenHearts.png");
        }   
        
        c.switchOffMouse(); 
        
        addCardsToList (c);
        playSound(); 
       
    }
    
    public void addCardsToList (Card c)
    {
            pickedCards.add (c);
            turns++; 
            
            if (turns == 2)
            {
                time = new javax.swing.Timer (1000, new TimerListener ());
                time.start (); 
            } 
    }
    
    public void playSound ()
    {
         AudioInputStream ais = null;
        try
            {
                ais = AudioSystem.getAudioInputStream (new File ("CardFlip.wav").getAbsoluteFile());
            }
        
            catch (UnsupportedAudioFileException e)
            
            {
                
            }
        
            catch (IOException io)
            {
                
            }
        
        if (ais != null)
        {
            try
                {
                    Clip clip = AudioSystem.getClip(); 
                    clip.open (ais);
                    clip.start(); 
                }    
            catch (LineUnavailableException l)
            {

            }
            
            catch (IOException io)
            {
                
            }
        }
    }
    
    public void cardSelected (ArrayList <Card> cards, int playerTurn)
    {
        Card card1 = cards.remove (0); 
        Card card2 = cards.remove (0); 
        Players p = players.get(playerTurn);
        
        
        if (card1.getName().equals(card2.getName())) 
        {
           
            p.addScore(); 
            printMessage(p.getLoginName() + " got a match! \nDealer replacing two cards");
            
            if(getNumberOfCards()!=0){
                    replaceCardAt(card1);
                    
                    if(getNumberOfCards()!=0){
                        replaceCardAt(card2);
                    }
                    
                    else
                        removeCard (card2); 
		}
                
                else
                {
                    removeCard (card2); 
                    removeCard (card1); 
                }

            } 
            
            else {
                    printMessage(p.getLoginName() + " did not have a match!");
                 }
            
            resetTurn(); 
            
    }
    
    public int getNumberOfCardsOnTable(){
		return cardsOnTable.size();
	}
    
    public int getNumberOfCards ()
    {
        return d.getNumberOfCards();
    }
    
    public void removeCard(Card card){
		JLabel currentScore;
                JPanel playerInfo = new JPanel();
                playerInfo.setPreferredSize (new Dimension (200,90));
                
                cardsOnTable.remove(card);
                
                cardPanel.removeAll(); 
                
                for (Players p: players)
                {
                    currentScore = new JLabel (p.getLoginName() + " : " + p.getScore());
                    currentScore.setPreferredSize (new Dimension (200, 20));
                    playerInfo.add (currentScore); 
                }
                
                cardPanel.add (playerInfo);
                
                for (Card cards: cardsOnTable)
                {
                    cardPanel.add(cards);
                }
             
                
            
                if (cardsOnTable.isEmpty())
                {
                    gameEnd(); 
                }
                
                frame.repaint(); 
                frame.revalidate(); 
        }	
        
    public void resetTurn () 
        {
            turns = 0 ; 
            playerTurn++;

            if (playerTurn == noOfPlayer)
                playerTurn = 0;
        }
    
    public void replaceCardAt(Card card){
            int counter = 0; 
            int no = 0;
            Card newCard; 
            JLabel currentScore;
            JPanel playerInfo = new JPanel();
            playerInfo.setPreferredSize (new Dimension (200,90));
            
            JPanel cardDeck = new JPanel();
            cardDeck.setPreferredSize (new Dimension (200,400));
            JLabel deckPic = new JLabel ();
            JLabel noOfCard = new JLabel ("No of Cards: "+ d.getNumberOfCards());
            deckPic.setIcon (new ImageIcon ("cardDeck.png"));
            cardDeck.add (deckPic);
            cardDeck.add (noOfCard); 
            
            for (Card c: cardsOnTable)
                {
                    if (c == card)
                        no = counter;
                    else 
                        counter++;
                }
            
            newCard = d.dealCard(); 
            newCard.addMouseListener (new MListener());
            
            cardsOnTable.set (no, newCard);
            cardPanel.removeAll(); 
            
            for (Players p: players)
            {
                currentScore = new JLabel (p.getLoginName() + " : " + p.getScore());
                currentScore.setPreferredSize (new Dimension (200, 20));
                playerInfo.add (currentScore); 
            }
            
            cardPanel.add (playerInfo);
            
            if (d.getNumberOfCards() != 0)
                cardPanel.add (cardDeck);
            
            for (Card cards: cardsOnTable)
            {
                cardPanel.add(cards);
            }
            
            frame.repaint();
            frame.revalidate(); 
            dealCardSound(); 
	}
    
    public void printMessage(String message){
		
                messageFrame = new JFrame ("Results");
                JPanel msgPanel = new JPanel (); 
                msgPanel.setPreferredSize (new Dimension (400,125));
                
                JLabel msg = new JLabel (message);
                msg.setPreferredSize (new Dimension (400,30));
                msg.setHorizontalAlignment (SwingConstants.CENTER);
                
                JButton okay = new JButton ("Okay");
                okay.setPreferredSize (new Dimension (100,30));
                okay.addActionListener (new okayButtonListener ());
                
                msgPanel.add (msg); 
                msgPanel.add (okay); 
                
                messageFrame.setPreferredSize (new Dimension (500,125));
                messageFrame.add (msgPanel);
                messageFrame.pack(); 
                messageFrame.setVisible (true); 
                               	
	}
    
    private class okayButtonListener implements ActionListener{
        
        public void actionPerformed (ActionEvent e)
        {         
            messageFrame.setVisible (false); 
            messageFrame.removeAll(); 
            
            if (cardsOnTable.isEmpty())
            {
                gameEnd();
            } 
            
            else
            {
                cm.sendOkay (); 
            }
        }
    }
    
    public void carryOn ()
    {
        messageFrame.setVisible (false); 
        messageFrame.removeAll(); 
        resetBoard (); 
    }
    
    public void gameEnd () 
    {  
       cardPanel.removeAll(); 
       JLabel GameEnd = new JLabel ("Game End");
       cardPanel.add (GameEnd);
       frame.revalidate(); 
       
       messageFrame.setVisible (false); 
        messageFrame.removeAll(); 
       
       compareScore(); 
      
    }
    
    public void compareScore()
        {
            int highest = 0; 
            int counter = 0; 
            ArrayList <String> name = new ArrayList <> (); 
            String toPrint = ""; 
            Players winner = null; 
 
            
            for (Players p : players)
            {
                if (highest < p.getScore())
                    {
                        highest = p.getScore();
                    } 
            }
            
            for (Players p : players)
            {
                if (highest == p.getScore())
                    {
                        counter++;
                    }
            }
            
            for (Players p: players)
            {
                if (highest == p.getScore())
                    {
                        name.add(p.getLoginName());
                    }          
            }
            
            if (counter == 1)
            {
               
                for (Players p: players)
                {
                    if (highest == p.getScore())
                       winner = p;          
                }
                
                if (!(winner instanceof ComputerPlayer))
                {
                    
                    cm.addScore (loginName);
                } 
                     
                printFinalMessage (name.get(0) + " won! Score: " + highest);
            }
            
            else
            {
                for (String n: name)
                {
                    toPrint = toPrint + " , " + n;                    
                    
                    printFinalMessage (toPrint + " has tied! Score: " + highest);
                }
            }
            
            name.clear(); 
        }
    
    public void printFinalMessage(String message){
		
                messageFrame = new JFrame ("Results");
        
                JPanel msgPanel = new JPanel (); 
                msgPanel.setPreferredSize (new Dimension (400,125));
                
                JLabel msg = new JLabel (message);
                msg.setPreferredSize (new Dimension (400,30));
                msg.setHorizontalAlignment (SwingConstants.CENTER);
                
                JButton lastOkay = new JButton ("Okay");
                lastOkay.setPreferredSize (new Dimension (100,30));
                lastOkay.addActionListener (new lastButtonListener());
                
                msgPanel.add (msg); 
                msgPanel.add (lastOkay); 
                
                messageFrame.setPreferredSize (new Dimension (500,125));
                messageFrame.add (msgPanel);
                messageFrame.pack(); 
                messageFrame.setVisible (true); 
                	
	}
    
    private class lastButtonListener implements ActionListener {
        public void actionPerformed (ActionEvent e)
        {
            System.out.println ("Bye");
            messageFrame.setVisible (false); 
            System.exit (0); 
        }
    }
    
    
    public void resetBoard () 
    {
        for (Card c: cardsOnTable)
        {
            c.changeImage ("CardBack.png");
            c.switchOnMouse(); 
        }
        playerTurn();
    }
    
    public void playerTurn() 
    {
        Players p; 
        
        p = players.get (playerTurn);
        
        if (!cardsOnTable.isEmpty())
            nextMove (p);
      
        
        if (playerTurn > noOfPlayer)
            playerTurn = 0 ; 
        
    }
    
    public void nextMove (Players p) 
        {
            if (p instanceof ComputerPlayer )
            {
                if (loginName.equals (players.get(0).getLoginName())) 
                    if (cardsOnTable.size() != 0)
                        computerNextMove();
           
            }
        }
    
    public void computerNextMove () 
    {   
        cm.makeGuess (cardsOnTable);   
    }
    
    public void dealCardSound ()
    {
         AudioInputStream ais = null;
        try
            {
                ais = AudioSystem.getAudioInputStream (new File ("DealCard.wav").getAbsoluteFile());
            }
        
            catch (UnsupportedAudioFileException e)
            
            {
                
            }
        
            catch (IOException io)
            {
                
            }
        
        if (ais != null)
        {
            try
                {
                    Clip clip = AudioSystem.getClip(); 
                    clip.open (ais);
                    clip.start(); 
                }    
            catch (LineUnavailableException l)
            {

            }
            
            catch (IOException io)
            {
                
            }
        }
    }
}
