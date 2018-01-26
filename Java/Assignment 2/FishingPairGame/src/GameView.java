/*
 * CSCI 213 Assignment 2 
--------------------------
 * File name: GameView.java
 * Author : Chang Qi Jia 
 * Student Number : 5280618 09
 * Description : Main Code for the Game : "View"
 */

import java.util.*; 

public class GameView {
   private Deck currentDeck; 
   private ArrayList <Cards> cardsOnTable; 
   
   public GameView ()
   {
        Cards temp; 

               cardsOnTable = new ArrayList <Cards> ();
               currentDeck = new Deck (); 
               System.out.println ("Dealer Shuffles Deck");
               currentDeck.shuffle (); 

               System.out.println ("---------------------------------------------------------------------------");
               System.out.println ("15 cards dealt to the table");
               System.out.println ("---------------------------------------------------------------------------");
               for (int i = 1 ; i < 16 ; i++) 
               {
                   temp = currentDeck.dealCards ();
                   cardsOnTable.add (temp);
               }      
   }
   
   public void printTable ()
   {
       int counter = 0; 
       
       for (int i = 0 ; i < cardsOnTable.size() ; i ++) 
       {
            System.out.print ("<Card " + (i+1) + "> ");
            counter++;
            
            if ((counter % 5 )== 0)
                System.out.print ("\n");
       } 
       
   }
   
   public void showTable ()
   {
      int counter = 0; 
      
       for (int i = 0 ; i < cardsOnTable.size() ; i ++) 
       {
           System.out.print (cardsOnTable.get (i));
           counter ++;
           
           if ((counter % 5 )== 0)
               System.out.print ("\n");
       } 
   }
   
   public void showCards (int index)
   {
        int counter = 0; 
       
       for (int i = 0 ; i < cardsOnTable.size() ; i ++) 
       {   
               if (index == (i+1))
                   System.out.print (cardsOnTable.get (i));
               else
                   System.out.print ("<Card " + (i+1) + "> ");
               
               counter ++;
               
               if ((counter % 5 )== 0)
                  System.out.print ("\n");
       } 
   }
   
   public void showBothCards (int index1, int index2)
   {
       int counter = 0; 
       
       for (int i = 0 ; i < cardsOnTable.size() ; i ++) 
       { 
           
            if (index1 == (i+1) || index2 == (i+1))
                   System.out.print (cardsOnTable.get (i));
            else
                   System.out.print ("<Card " + (i+1) + "> ");
           
           counter ++;
               
               if ((counter % 5 )== 0)
                  System.out.print ("\n");
       } 
   }
   
   public void updateCards (int index1)
   {
      Cards temp; 
    
      temp = currentDeck.dealCards ();
      cardsOnTable.set (index1-1, temp);
     
   }
   
   public void replaceCards (int index1)
   {
      Cards temp; 
      
      temp = cardsOnTable.get (index1-1);
      currentDeck.addCards (temp);
      
      temp = currentDeck.dealCards ();
      cardsOnTable.set (index1-1, temp);
     
   }
   
   public boolean isEmpty ()
   {           
      return currentDeck.isEmpty(); 
   }
   
   public void removeCards (int index1)
   {
        cardsOnTable.remove(index1-1);    
   }
   
   public boolean matchCards (int firstCard, int secondCard)
   {
       Cards a , b;
       boolean match = false; 
       
       a = cardsOnTable.get(firstCard-1);
       b = cardsOnTable.get (secondCard-1);
       
       if (a.getName().equals(b.getName()))
       {
           match = true;
           System.out.println ("Succesful Match!");
       } 
       
       return match;
   }
   
    public boolean validGuess (int guess)
    {
       boolean validGuess = true; 
       
       int size = cardsOnTable.size();
       
       if (size < guess || guess <= 0)
       {
           if (guess != 99)
           {
            validGuess = false; 
            System.out.println ("The integer you keyed in is invalid, please key it within 1 to " + cardsOnTable.size() + "\n");
           }
       }

       return validGuess;
    }
   
   public int showDeck ()
   {
      return currentDeck.size(); 
   }
   
   public int showSize ()
   {
      return cardsOnTable.size(); 
   }
   
   public boolean isFinished ()
   {           
      return cardsOnTable.isEmpty(); 
   }
   
   public int findMatch ()
   {           
      int answer = 1;
      String tempAnswer = " ";
      String checkSuit = " ";
      
      for (Cards matchingName: cardsOnTable)
        {
             tempAnswer = matchingName.getName(); 
             checkSuit = matchingName.getSuits(); 
             
             for (Cards matchingCards: cardsOnTable)
             {
                 if (matchingCards.getName().equals(tempAnswer))
                     if (!(matchingCards.getSuits().equals(checkSuit)))
                         return answer;
             }
             answer++; 
        }
      return answer; 
   }
   
   public static void main (String [] args)
   {
       GameView newTable;
       boolean empty = false; 
       
       newTable = new GameView ();
       newTable.printTable (); 
     
       newTable.showTable();
       
       newTable.showCards (5);
       newTable.showCards (10);
             

      newTable.updateCards (5);
       
       
       newTable.showCards (5);
       newTable.showCards (10);
     
   }
}
