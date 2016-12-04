import { Component } from '@angular/core';

import { NavController } from 'ionic-angular';
import { DatePicker } from 'ionic-native';

@Component({
  selector: 'page-alarm',
  templateUrl: 'alarm.html'
})
export class AlarmPage {
  private DayNames : string[] = ["Monday", "Tuesday", "Wednesday",
                                 "Thursday", "Friday", "Satarday", "Sunday"];

  private Alarms : Date[] = new Array();
  private AlarmsEnabled : boolean[] = new Array();

  constructor(public navCtrl: NavController) {

  }

  private onSave() {
    var alarms = {};

    console.log(this.Alarms[0]);

    for (var i = 0; i < 7; i++) {
      var dayName = this.DayNames[i].toLowerCase();
      alarms[dayName] = {};
      alarms[dayName]["time"] = this.Alarms[i];
      alarms[dayName]["enabled"] = (this.AlarmsEnabled[i] == true);
    }

    console.log(alarms);

    //for (let day of this.DayNames) {
    //  alarms[day][time] =
    //}

    //console.log(this.Alarms);
  }
}
