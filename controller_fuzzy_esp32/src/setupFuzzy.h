#ifndef SETUPFUZZY_H
#define SETUPFUZZY_H
#include "config.h"

void setupFuzzy()
{
    // FuzzyInput
    FuzzySet *temperature_cold = new FuzzySet(0, 7, 14, 22);
    FuzzySet *temperature_comfortable = new FuzzySet(22, 25, 28, 31);
    FuzzySet *temperature_hot = new FuzzySet(31, 37, 44, 50);

    FuzzyInput *temperature = new FuzzyInput(1);
    temperature->addFuzzySet(temperature_cold);
    temperature->addFuzzySet(temperature_comfortable);
    temperature->addFuzzySet(temperature_hot);
    fuzzy->addFuzzyInput(temperature);

    FuzzySet *pH_acidic = new FuzzySet(0, 2, 4, 6.5);
    FuzzySet *pH_neutral = new FuzzySet(6.5, 7, 7.5, 8);
    FuzzySet *pH_basic = new FuzzySet(7.5, 10, 13, 30);

    FuzzyInput *pH = new FuzzyInput(2);
    pH->addFuzzySet(pH_acidic);
    pH->addFuzzySet(pH_neutral);
    pH->addFuzzySet(pH_basic);
    fuzzy->addFuzzyInput(pH);

    FuzzySet *heater_on = new FuzzySet(1, 1, 1, 1);
    FuzzySet *heater_off = new FuzzySet(0, 0, 0, 0);

    FuzzyOutput *heater = new FuzzyOutput(1);
    heater->addFuzzySet(heater_on);
    heater->addFuzzySet(heater_off);
    fuzzy->addFuzzyOutput(heater);

    FuzzySet *cooler_on = new FuzzySet(1, 1, 1, 1);
    FuzzySet *cooler_off = new FuzzySet(0, 0, 0, 0);

    FuzzyOutput *cooler = new FuzzyOutput(2);
    cooler->addFuzzySet(cooler_on);
    cooler->addFuzzySet(cooler_off);
    fuzzy->addFuzzyOutput(cooler);

    FuzzySet *pump_on = new FuzzySet(1, 1, 1, 1);
    FuzzySet *pump_off = new FuzzySet(0, 0, 0, 0);

    FuzzyOutput *pump = new FuzzyOutput(3);
    pump->addFuzzySet(pump_on);
    pump->addFuzzySet(pump_off);
    fuzzy->addFuzzyOutput(pump);
    
    //---------------------------------------------------------------------------------------------
    // Role
    FuzzyRuleAntecedent *if_temperature_cold_AND_pH_acidic = new FuzzyRuleAntecedent();
    if_temperature_cold_AND_pH_acidic->joinWithAND(temperature_cold, pH_acidic);

    FuzzyRuleAntecedent *if_temperature_cold_AND_pH_neutral = new FuzzyRuleAntecedent();
    if_temperature_cold_AND_pH_neutral->joinWithAND(temperature_cold, pH_neutral);

    FuzzyRuleAntecedent *if_temperature_cold_AND_pH_basic = new FuzzyRuleAntecedent();
    if_temperature_cold_AND_pH_basic->joinWithAND(temperature_cold, pH_basic);

    FuzzyRuleAntecedent *if_temperature_comfortable_AND_pH_acidic = new FuzzyRuleAntecedent();
    if_temperature_comfortable_AND_pH_acidic->joinWithAND(temperature_comfortable, pH_acidic);

    FuzzyRuleAntecedent *if_temperature_comfortable_OR_pH_neutral = new FuzzyRuleAntecedent();
    if_temperature_comfortable_OR_pH_neutral->joinWithAND(temperature_comfortable, pH_neutral);

    FuzzyRuleAntecedent *if_temperature_comfortable_AND_pH_basic = new FuzzyRuleAntecedent();
    if_temperature_comfortable_AND_pH_basic->joinWithOR(temperature_comfortable, pH_basic);

    FuzzyRuleAntecedent *if_temperature_hot_AND_pH_acidic = new FuzzyRuleAntecedent();
    if_temperature_hot_AND_pH_acidic->joinWithAND(temperature_hot, pH_acidic);

    FuzzyRuleAntecedent *if_temperature_hot_AND_pH_neutral = new FuzzyRuleAntecedent();
    if_temperature_hot_AND_pH_neutral->joinWithAND(temperature_hot, pH_neutral);

    FuzzyRuleAntecedent *if_temperature_hot_AND_pH_basic = new FuzzyRuleAntecedent();
    if_temperature_hot_AND_pH_basic->joinWithAND(temperature_hot, pH_basic);

    //heater and pump
    FuzzyRuleConsequent *then_heater_on_and_pump_on = new FuzzyRuleConsequent();
    then_heater_on_and_pump_on->addOutput(heater_on);
    then_heater_on_and_pump_on->addOutput(pump_on);

    FuzzyRuleConsequent *then_heater_on_and_pump_off = new FuzzyRuleConsequent();
    then_heater_on_and_pump_off->addOutput(heater_on);
    then_heater_on_and_pump_off->addOutput(pump_off);

    FuzzyRuleConsequent *then_heater_off_and_pump_on = new FuzzyRuleConsequent();
    then_heater_off_and_pump_on->addOutput(heater_off);
    then_heater_off_and_pump_on->addOutput(pump_on);

    FuzzyRuleConsequent *then_heater_off_and_pump_off = new FuzzyRuleConsequent();
    then_heater_off_and_pump_off->addOutput(heater_off);
    then_heater_off_and_pump_off->addOutput(pump_off);

    //cooler and pump
    FuzzyRuleConsequent *then_cooler_on_and_pump_on = new FuzzyRuleConsequent();
    then_cooler_on_and_pump_on->addOutput(cooler_on);
    then_cooler_on_and_pump_on->addOutput(pump_on);

    FuzzyRuleConsequent *then_cooler_on_and_pump_off = new FuzzyRuleConsequent();
    then_cooler_on_and_pump_off->addOutput(cooler_on);
    then_cooler_on_and_pump_off->addOutput(pump_off);

    FuzzyRuleConsequent *then_cooler_off_and_pump_on = new FuzzyRuleConsequent();
    then_cooler_off_and_pump_on->addOutput(cooler_off);
    then_cooler_off_and_pump_on->addOutput(pump_on);

    FuzzyRuleConsequent *then_cooler_off_and_pump_off = new FuzzyRuleConsequent();
    then_cooler_off_and_pump_off->addOutput(cooler_off);
    then_cooler_off_and_pump_off->addOutput(pump_off);


    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, if_temperature_cold_AND_pH_acidic, then_heater_on_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule1);

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, if_temperature_cold_AND_pH_neutral, then_heater_on_and_pump_off);
    fuzzy->addFuzzyRule(fuzzyRule2);

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, if_temperature_cold_AND_pH_basic, then_heater_on_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule3);

    FuzzyRule *fuzzyRule4 = new FuzzyRule(4, if_temperature_comfortable_AND_pH_acidic, then_heater_off_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule4);

    FuzzyRule *fuzzyRule5 = new FuzzyRule(5, if_temperature_comfortable_OR_pH_neutral, then_heater_off_and_pump_off);
    fuzzy->addFuzzyRule(fuzzyRule5);

    FuzzyRule *fuzzyRule6 = new FuzzyRule(6, if_temperature_comfortable_AND_pH_basic, then_heater_off_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule6);

    FuzzyRule *fuzzyRule7 = new FuzzyRule(7, if_temperature_hot_AND_pH_acidic, then_cooler_on_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule7);    

    FuzzyRule *fuzzyRule8 = new FuzzyRule(8, if_temperature_hot_AND_pH_neutral, then_cooler_on_and_pump_off);
    fuzzy->addFuzzyRule(fuzzyRule8);

    FuzzyRule *fuzzyRule9 = new FuzzyRule(9, if_temperature_hot_AND_pH_basic, then_cooler_on_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule9);

    FuzzyRule *fuzzyRule10 = new FuzzyRule(10, if_temperature_comfortable_AND_pH_acidic, then_cooler_off_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule10);

    FuzzyRule *fuzzyRule11 = new FuzzyRule(11, if_temperature_comfortable_OR_pH_neutral, then_cooler_off_and_pump_off);
    fuzzy->addFuzzyRule(fuzzyRule11);

    FuzzyRule *fuzzyRule12 = new FuzzyRule(12, if_temperature_comfortable_AND_pH_basic, then_cooler_off_and_pump_on);
    fuzzy->addFuzzyRule(fuzzyRule12);
}
#endif // SETUPFUZZY_H