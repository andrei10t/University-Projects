
import java.util.Comparator;
import temapoo.Factura;
import temapoo.Magazin;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Star Lord
 */
public class ComparaFacturi implements Comparator<Factura>{
    public int compare(Factura a, Factura b){
        return (int) (50* (a.getTotalFaraTaxe()-b.getTotalFaraTaxe()));
    }
}
