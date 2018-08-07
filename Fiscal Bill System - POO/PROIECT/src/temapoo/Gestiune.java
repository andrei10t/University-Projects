/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temapoo;

import java.text.DecimalFormat;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Vector;

/**
 *
 * @author Star Lord
 */
public class Gestiune {

    private static Gestiune gestiune = new Gestiune();
    List<Produs> produse;
    List<Magazin> magazine;
    Map<String, Map<String, Integer>> taxe;
    Vector<String> tari;

    private Gestiune() {
        Citiri citire = new Citiri();
        produse = citire.citireProduse();
        magazine = citire.citireMagazinFacturi();
        taxe = citire.citireTaxe();
        tari = citire.citireTari();
    }

    public static Gestiune getInstance() {
        return gestiune;
    }

    public static void main(String[] args) {
        Gestiune out = getInstance();
        DecimalFormat numberFormat = new DecimalFormat("#.####");
        Collections.sort(out.magazine, new ComparaMagazinele());
        System.out.println("MiniMarket");
        for (Magazin m : out.magazine) {
            //Collections.sort(m.magazin, new ComparaFacturile());
            if (m instanceof MiniMarket) {
                System.out.println(m.nume);
                System.out.println();
                System.out.println("Total " + numberFormat.format(m.getTotalFaraTaxe()) + " "
                        + numberFormat.format(m.getTotalCuTaxe()) + " " + numberFormat.format(m.getTotalCuTaxeScutite()));
                System.out.println();
                System.out.println("Tara");
                for (String tara : out.tari) {
                    if (m.getTotalTaraFaraTaxe(tara) == 0) {
                        System.out.println(tara + " 0");
                    } else {
                        System.out.println(tara + " " + numberFormat.format(m.getTotalTaraFaraTaxe(tara))
                                + " " + numberFormat.format(m.getTotalTaraCuTaxe(tara))
                                + " " + numberFormat.format(m.getTotalTaraCuTaxeScutite(tara)));
                    }
                }
                System.out.println();
                for (Factura f : m.magazin) {
                    System.out.println(f.denumire);
                    System.out.println();
                    System.out.println("Total " + numberFormat.format(f.getTotalFaraTaxe()) + " "
                            + numberFormat.format(f.getTotalCuTaxe()));
                    System.out.println();
                    System.out.println("Tara");
                    for (String tara : out.tari) {
                        if (f.getTotalTaraFaraTaxe(tara) == 0) {
                            System.out.println(tara + " 0");
                        } else {
                            System.out.println(tara + " " + numberFormat.format(f.getTotalTaraFaraTaxe(tara))
                                    + " " + numberFormat.format(f.getTotalTaraCuTaxe(tara)));
                        }
                    }
                }
                System.out.println();
            }
        }
        System.out.println("MediumMarket");
        for (Magazin m : out.magazine) {
            if (m instanceof MediumMarket) {
                System.out.println(m.nume);
                System.out.println();
                System.out.println("Total " + numberFormat.format(m.getTotalFaraTaxe()) + " "
                        + numberFormat.format(m.getTotalCuTaxe()) + " " + numberFormat.format(m.getTotalCuTaxeScutite()));
                System.out.println();
                System.out.println("Tara");
                for (String tara : out.tari) {
                    if (m.getTotalTaraFaraTaxe(tara) == 0) {
                        System.out.println(tara + " 0");
                        System.out.println(0);
                    } else {
                        System.out.println(tara + " " + numberFormat.format(m.getTotalTaraFaraTaxe(tara))
                                + " " + numberFormat.format(m.getTotalTaraCuTaxe(tara))
                                + " " + numberFormat.format(m.getTotalTaraCuTaxeScutite(tara)));
                    }
                }
               
                System.out.println();
                for (Factura f : m.magazin) {
                    System.out.println(f.denumire);
                    System.out.println();
                    System.out.println("Total " + numberFormat.format(f.getTotalFaraTaxe()) + " "
                            + numberFormat.format(f.getTotalCuTaxe()));
                    System.out.println();
                    System.out.println("Tara");
                    for (String tara : out.tari) {
                        if (f.getTotalTaraFaraTaxe(tara) == 0) {
                            System.out.println(tara + " 0");
                        } else {
                            System.out.println(tara + " " + numberFormat.format(f.getTotalTaraFaraTaxe(tara))
                                    + " " + numberFormat.format(f.getTotalTaraCuTaxe(tara)));
                        }
                    }
                }
                System.out.println();
            }
        }
        System.out.println("HyperMarket");
        for (Magazin m : out.magazine) {
            if (m instanceof HyperMarket) {
                System.out.println(m.nume);
                System.out.println();
                System.out.println("Total " + numberFormat.format(m.getTotalFaraTaxe()) + " "
                        + numberFormat.format(m.getTotalCuTaxe()) + " " + numberFormat.format(m.getTotalCuTaxeScutite()));
                System.out.println();
                System.out.println("Tara");
                for (String tara : out.tari) {
                    if (m.getTotalTaraFaraTaxe(tara) == 0) {

                        System.out.println(tara + " 0");
                    } else {
                        System.out.println(tara + " " + numberFormat.format(m.getTotalTaraFaraTaxe(tara))
                                + " " + numberFormat.format(m.getTotalTaraCuTaxe(tara))
                                + " " + numberFormat.format(m.getTotalTaraCuTaxeScutite(tara)));
                    }
                }
                System.out.println();
                
                for (Factura f : m.magazin) {
                    System.out.println(f.denumire);
                    System.out.println();
                    System.out.println("Total " + numberFormat.format(f.getTotalFaraTaxe()) + " "
                            + numberFormat.format(f.getTotalCuTaxe()));
                    System.out.println();
                    System.out.println("Tara");
                    for (String tara : out.tari) {
                        if (f.getTotalTaraFaraTaxe(tara) == 0) {
                            System.out.println(tara + " 0");
                        } else {
                            System.out.println(tara + " " + numberFormat.format(f.getTotalTaraFaraTaxe(tara))
                                    + " " + numberFormat.format(f.getTotalTaraCuTaxe(tara)));
                        }
                    }
                }
               // System.out.println();
            }
        }

    }
}
