

import java.util.*; 
import java.io.*; 

public class DisplayPlayerScore {
    public static void playerScore () 
    {
        System.out.println ("\nOption 6: Displaying all player score\n");
        
        try 
                {
                    printPlayerScore ("players.dat");        
                }
            
            catch (FileNotFoundException ex)
                {
                   System.out.print ("File players.dat cannot be found. Please create the file using Option 2. Create a player\n");
                }
        
            catch (IOException error)
                {
                    System.out.print ("Error in displaying player info, please ensure that there is no folder or file named players.dat\n");
                } 
    }

    public static void printPlayerScore (String args) throws IOException 
    {
        Scanner input = new Scanner (System.in);
        String tempScore; 
        int counter = 0; 
        int highest, swapTemp; 
        
        String [] name = new String [10]; 
        int [] score = new int [10];
        
        Scanner fileInput;
        fileInput = new Scanner (new File (args)); 
        
        String temp;
        String [] dummy = new String [4]; 

        System.out.println ("Player Name\tScore");
        System.out.println ("*********************");
        
       while (fileInput.hasNextLine())
        {
            temp = fileInput.nextLine ();
            
            dummy = temp.split ("\\|");
            name [counter] = dummy [0];
            tempScore = dummy[3];
            score [counter] = Integer.parseInt (tempScore);
            
            counter++; 
        } 
      
       for (int j = 0; j < counter ; j++)
       {
            for (int i = 0; i < counter-1; i++)
             {
                 if (score [i] < score [i+1])
                 {
                     swapTemp = score[i];
                     score [i] = score[i+1];
                     score [i+1] = swapTemp; 

                     temp = name[i]; 
                     name[i] = name[i+1]; 
                     name[i+1] = temp; 

                 }
              }
        }
       
       for (int i = 0; i < counter; i++)
       {
           System.out.println (name[i] + "\t\t" + score[i]);
       }
       
        fileInput.close (); 
      
    }
}
