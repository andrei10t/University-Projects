/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 *
 * @author Star Lord
 */
public class Dictionar {

    Scanner scanTaxe = null;

    public void openFile() {
        try {
            scanTaxe = new Scanner(new File("taxe.txt"));
        } catch (Exception e) {
            System.out.println("taxe.txt not found");
            e.printStackTrace();
        }
    }

    public Map<String, Map<String, Integer>> citireTaxe() {
        Map<String, Integer> categorieProcent = new HashMap<String, Integer>();
        Map<String, Map<String, Integer>> taxe = new HashMap<String, Map<String, Integer>>();

        String line = scanTaxe.nextLine();
        String[] tari = line.split(" ");
        int len = tari.length;
        while (scanTaxe.hasNext()) {
            line = scanTaxe.nextLine();
            String[] details = line.split(" ");

            for (int i = 1; i < len; i++) {
                categorieProcent.put(details[0], Integer.parseInt(details[i]));
                taxe.put(tari[i], categorieProcent);
            }
        }
        return taxe;
    }

    public static void main(String[] args) {
        Dictionar d= new Dictionar();
        Map<String, Map<String, Integer>> taxe = new HashMap<String, Map<String, Integer>>();
        d.openFile();
        taxe=d.readFile();
        System.out.println(taxe);
    }
}
