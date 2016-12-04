import { Component } from '@angular/core';

import { AlarmPage } from '../alarm/alarm';
import { LightPage } from '../light/light';
import { SettingsPage } from '../settings/settings';

@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {
  // this tells the tabs component which Pages
  // should be each tab's root Page
  tab1Root: any = LightPage;
  tab2Root: any = AlarmPage;
  tab3Root: any = SettingsPage;

  constructor() {

  }
}
