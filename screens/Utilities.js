import React, { Component } from "react";
import {StyleSheet} from "react-native";
import NumericInput from 'react-native-numeric-input'
import {Block, Text, Button } from "../components";
import { DataTable } from 'react-native-paper';
import { theme} from "../constants";

class Settings extends Component {

  constructor()
  {
      super();
      this.state={Num1:0,Num2:5.78,Num3:0,Num4:0,Num5:35,Num6:0,total:0}
  }

  Sum=()=>
  {
     var N1=this.state.Num1;
     var N2=this.state.Num2;
     var N3=this.state.Num3;
     var N4=this.state.Num4;
     var N5=this.state.Num5;
     var N6=this.state.Num6;
      
     var bill = (N1*N2)+N3+N4+N5+N6;
     this.setState({total: bill});

  } 
  
  render() {
    

    return (
      <Block>
        <Block flex={false} row center space="between" style={styles.header}>
          <Text h1 bold>
            Estimate Bills
          </Text>
        </Block>
        <Block>
        <DataTable >

    <DataTable.Header>
      <DataTable.Title>No</DataTable.Title>
      <DataTable.Title style={{flex: 4}}>Title</DataTable.Title>
      <DataTable.Title >Cost</DataTable.Title>
    </DataTable.Header>


    <DataTable.Row>
      <DataTable.Cell>1</DataTable.Cell>
      <DataTable.Cell style={{flex: 3}}>Unit consumed</DataTable.Cell>
      <NumericInput onChange={Num1 => console.log(Num1),Num1 => this.setState({Num1})}
            
            minValue = {0}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={47} 
            iconSize={10} />
    </DataTable.Row>
    <DataTable.Row>
      <DataTable.Cell>2</DataTable.Cell>
      <DataTable.Cell style={{flex: 3}}>Cost of Unit</DataTable.Cell>
      <NumericInput onChange={Num2 => console.log(Num2),Num2 => this.setState({Num2})}
            initValue = {5.78}
            minValue = {0}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={47} 
            iconSize={10} />
    </DataTable.Row>
    <DataTable.Row>
      <DataTable.Cell>3</DataTable.Cell>
      <DataTable.Cell style={{flex: 3}}>GST</DataTable.Cell>
      <NumericInput onChange={Num3 => console.log(Num3),Num3 => this.setState({Num3})}
            minValue = {0}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={47} 
            iconSize={10} />
    </DataTable.Row>
    <DataTable.Row>
      <DataTable.Cell>4</DataTable.Cell>
      <DataTable.Cell style={{flex: 3}}>Income Tax</DataTable.Cell>
      <NumericInput onChange={Num4 => console.log(Num4),Num4 => this.setState({Num4})}
            minValue = {0}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={47} 
            iconSize={10} />
    </DataTable.Row>
    <DataTable.Row>
      <DataTable.Cell>5</DataTable.Cell>
      <DataTable.Cell style={{flex: 3}}>Ptv Fee</DataTable.Cell>
      <NumericInput onChange={Num5 => console.log(Num5),Num5 => this.setState({Num5})}
            minValue = {0}
            initValue = {35}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={47} 
            iconSize={10} />
    </DataTable.Row>
    <DataTable.Row>
      <DataTable.Cell>6</DataTable.Cell>
      <DataTable.Cell style={{flex: 3}}>Fuel Adjustment</DataTable.Cell>
      <NumericInput onChange={Num6 => console.log(Num6),Num6 => this.setState({Num6})}
            type = 'up-down'
            totalWidth={100} 
            totalHeight={47} 
            iconSize={10} />
    </DataTable.Row>
    <DataTable.Row>
        <DataTable.Cell numeric><Text bold color = "red">Total  </Text></DataTable.Cell>
        <DataTable.Cell><Text bold h3>{this.state.total.toFixed(2)} Rs/-</Text></DataTable.Cell>
    </DataTable.Row>
  </DataTable>
        </Block>
        <Block middle flex={0.5} margin={[100, theme.sizes.padding * 2]}>
        <Button gradient onPress={this.Sum}>
            <Text center bold white>
              Sum Total Amount
            </Text>
          </Button>
          </Block>
      </Block>
    );
  }
}



export default Settings;

const styles = StyleSheet.create({
  header: {
    paddingHorizontal: theme.sizes.base * 2
  }
});