/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.io.File;
import java.util.Scanner;

/**
 *
 * @author Star Lord
 */
public class TemaPOO {
 private Scanner scan;
    
    public void openFile(){
        try{
            scan=new Scanner(new File("produse.txt"));
        }
        catch(Exception e){
            System.out.println("produse.txt not found");        
        }
    }
    
    public void readFile(){
        
         
    }
     public void closeFile(){
        scan.close();
    }
   
    public static void main(String[] args) {
       TemaPOO r = new TemaPOO();
       r.openFile();
       r.readFile();
       r.closeFile();
    }
    
}
