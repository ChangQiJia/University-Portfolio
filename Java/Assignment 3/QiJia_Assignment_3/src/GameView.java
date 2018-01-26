/*
* CSCI213 Assignment 3
* --------------------------
* File name: GameView.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: The GUI of the game
*/

import java.util.*;
import javax.swing.*; 
import java.awt.*; 
import java.awt.event.*; 
import javax.sound.sampled.*;
import java.io.*; 

public class GameView extends JFrame{

	private ArrayList<Card> cardsOnTable;
	private int maxNumber = 4;
        private ViewController vc; 
        private GameController gc; 
        private int turns;
        private int playerNo = 0;
        private Card cardChosen; 
        private Point click; 
        private ArrayList<Card> pickedCards = new ArrayList <Card> ();
        private JFrame messageFrame = new JFrame("Results"); 
        private JPanel cardPanel;
        private javax.swing.Timer time;
        private Deck d; 
        private ArrayList<GamePlayerInterface> players;
        private int playerTurn = 0; 
        
        public GameView (ViewController vc, GameController gc, ArrayList<GamePlayerInterface> players)
        {
            this.vc = vc; 
            this.gc = gc; 
            this.players = players; 
            cardsOnTable = new ArrayList<Card>();
            Card c; 
            d = new Deck(); 
            JLabel currentScore;
            JPanel playerInfo = new JPanel();
            playerInfo.setPreferredSize (new Dimension (200,50));
            
            cardPanel = new JPanel (); 
            
            d.shuffle(); 
            
            for (int i = 0; i < 5 ; i++)
            {
                c = d.dealCard(); 
                addCard (c);
            }
            
            JPanel cardDeck = new JPanel();
            cardDeck.setPreferredSize (new Dimension (200,400));
            JLabel deckPic = new JLabel ();
            JLabel noOfCard = new JLabel ("No of Cards: "+ d.getNumberOfCards());
            deckPic.setIcon (new ImageIcon ("cardDeck.png"));
            cardDeck.add (deckPic);
            cardDeck.add (noOfCard); 
            
            for (GamePlayerInterface p: players)
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
           
            add (cardPanel); 
            
            setPreferredSize (new Dimension (1600,500)); 
            pack(); 
            setVisible (false); 
        }
        
	public void replaceCardAt(Card card){
            int counter = 0; 
            int no = 0;
            Card newCard; 
            JLabel currentScore;
            JPanel playerInfo = new JPanel();
            playerInfo.setPreferredSize (new Dimension (200,50));
            
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
            
            for (GamePlayerInterface p: players)
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
            
            repaint();
            revalidate(); 
            dealCardSound(); 
            
	}
	
	public void addCard(Card card){
		dealCardSound(); 
                cardsOnTable.add(card);
                cardPanel.add (card); 
                repaint();
                revalidate(); 
                
	}
	
	public int getNumberOfCardsOnTable(){
		return cardsOnTable.size();
	}
	
	public void removeCard(Card card){
		JLabel currentScore;
                JPanel playerInfo = new JPanel();
                playerInfo.setPreferredSize (new Dimension (200,50));
                
                cardsOnTable.remove(card);
                
                cardPanel.removeAll(); 
                
                for (GamePlayerInterface p: players)
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
                
                repaint(); 
                revalidate(); 
        }	

	public void showFaceDownCards(){
		for(int i=0;i<cardsOnTable.size();i++){
			System.out.print("< Card "+(i+1)+" >");
		}
		System.out.println();
	}
	
	public void printMessage(String message){
		
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
	
	public void printFinalMessage(String message){
		
                JPanel msgPanel = new JPanel (); 
                msgPanel.setPreferredSize (new Dimension (400,125));
                
                JLabel msg = new JLabel (message);
                msg.setPreferredSize (new Dimension (400,30));
                msg.setHorizontalAlignment (SwingConstants.CENTER);
                
                JButton okay = new JButton ("Okay");
                okay.setPreferredSize (new Dimension (100,30));
                okay.addActionListener (new lastOkayButtonListener ());
                
                msgPanel.add (msg); 
                msgPanel.add (okay); 
                
                messageFrame.setPreferredSize (new Dimension (500,125));
                messageFrame.add (msgPanel);
                messageFrame.pack(); 
                messageFrame.setVisible (true); 
                	
	}
        
        private class MListener implements MouseListener{
            
            
                       
            public void mouseClicked (MouseEvent event)
            {
        
                if (turns == 0)
                {
                    click = new Point (event.getPoint()); 
                    Object temp = event.getSource() ; 
                    cardChosen = (Card) temp; 
                    if (cardChosen.active())
                    {
                        showCard (cardChosen); 
                        turns++;
                    }
                }
                
                else if (turns == 1)
                {
                    click = new Point (event.getPoint()); 
                    Object temp = event.getSource() ; 
                    cardChosen = (Card) temp; 
                    
                    if (cardChosen.active())
                    {
                        showCard (cardChosen);
                        turns++;
                    
                        time = new javax.swing.Timer (500, new TimerListener());
                        time.start();
                    }

                }
                              
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
                gc.cardSelected (pickedCards, players.get(playerNo)); 
                time.stop();
            } 
        }
        
    public void showCard (Card newCard) 
    {   
        for (Card c: cardsOnTable)
        {
            if (c == newCard)
            {
                flipCard (c);
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
        boolean valid = true; 
        
        for (Card pc: pickedCards)
        {
            if (pc == c)
            {
                valid = false;
                turns--; 
            }
        }
        
        if (valid == true)
            pickedCards.add (c);
    }
    
    public Card getCard () 
    {
        Card c; 
        
        c = pickedCards.remove(0);
        
        if (pickedCards.isEmpty())
        {
            for (Card card: cardsOnTable)
            {
                card.changeImage ("CardBack.png");
            }
        }
        
        return c; 
    }
    
    private class okayButtonListener implements ActionListener{
        
        public void actionPerformed (ActionEvent e)
        {
            messageFrame.setVisible (false); 
            messageFrame.removeAll(); 
            messageFrame = new JFrame ("Results");
            
            if (cardsOnTable.isEmpty())
                gameEnd(); 
            else
                resetBoard(); 
        }
    }
    
    private class lastOkayButtonListener implements ActionListener{
        
        public void actionPerformed (ActionEvent e)
        {
            messageFrame.setVisible (false); 
            messageFrame.removeAll(); 
            nextGame(); 
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
    
    public void gameEnd () 
    {  
       gc.emptyTable();
       cardPanel.removeAll(); 
       JLabel GameEnd = new JLabel ("Game End");
       cardPanel.add (GameEnd);
       revalidate(); 
       
      gc.compareScore(); 
      
    }
    
    public void resetTurn () 
    {
        turns = 0 ; 
        playerNo++;
        
        if (playerNo == 2)
            playerNo = 0;
    }
    
    public int getNumberOfCards ()
    {
        return d.getNumberOfCards();
    }
    
    public void showView() 
    {
        setVisible(true); 
        int counter = 0 ; 
        
        playerTurn(); 

    }
    
    public void playerTurn() 
    {
        GamePlayerInterface p; 
        
        p = players.get (playerTurn);
        
        if (!cardsOnTable.isEmpty())
            gc.nextMove (p);
        
        playerTurn++;
        
        if (playerTurn > 1)
            playerTurn = 0 ; 
        
    }
    
    public void nextGame ()
    {
        messageFrame.removeAll(); 
        messageFrame = new JFrame ("Continue");
        
        JPanel panel = new JPanel(); 
        panel.setPreferredSize (new Dimension (350, 125));
        
        JLabel label = new JLabel ("Do you wish to play another game?");
        label.setPreferredSize (new Dimension (300,50));
        label.setHorizontalAlignment (SwingConstants.CENTER);
        
        JButton yes = new JButton ("Continue");
        yes.setPreferredSize (new Dimension (100,25));
        
        JButton no = new JButton ("Stop");
        no.setPreferredSize (new Dimension (100,25));
        
        yes.addActionListener (new contGameListener());
        no.addActionListener (new stopGameListener());
        
        panel.add (label); 
        panel.add (yes); 
        panel.add (no); 
        
        messageFrame.setPreferredSize (new Dimension (400, 150));
        messageFrame.add (panel); 
        messageFrame.pack(); 
        messageFrame.setVisible (true); 
           
    }
    
     private class contGameListener implements ActionListener{
        
        public void actionPerformed (ActionEvent e)
        {
            messageFrame.setVisible (false); 
            messageFrame.removeAll(); 
            messageFrame = new JFrame ("Results");
            
            for (GamePlayerInterface p : players)
            {
                p.setScore (0); 
            }
            
            gc.newGame();
        }
    }
     
    private class stopGameListener implements ActionListener{
        
        public void actionPerformed (ActionEvent e)
        {
            System.exit (0); 
        }
    }
    
    public void makeNextMove ()
    {
        int rand1 , rand2; 
        Random r = new Random (); 
        Card temp1, temp2; 
        
        rand1 = r.nextInt(cardsOnTable.size());
        
        do
        {
            rand2 = r.nextInt (cardsOnTable.size()); 
        } while (rand2 == rand1); 
        
        temp1 = cardsOnTable.get (rand1);
        temp2 = cardsOnTable.get (rand2); 
        
        flipCard (temp1); 
        flipCard (temp2); 
        
        time = new javax.swing.Timer (1000, new TimerListener());
        time.start(); 
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


