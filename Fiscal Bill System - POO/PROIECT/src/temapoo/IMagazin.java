/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

/**
 *
 * @author Star Lord
 */
public interface IMagazin {
    public double getTotalFaraTaxe();
    public double getTotalCuTaxe();
    public double getTotalCuTaxeScutite();
    public double getTotalTaraFaraTaxe(String tara);
    public double getTotalTaraCuTaxe(String tara);
    public double getTotalTaraCuTaxeScutite(String tara);
    public double calculScutiriTaxe();
}
