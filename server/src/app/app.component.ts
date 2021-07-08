import { Component, AfterViewInit, ViewChild } from '@angular/core';
import { AngularFireDatabase } from '@angular/fire/database';

import { MatPaginator } from '@angular/material/paginator';
import { MatTableDataSource } from '@angular/material/table';

import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

import * as moment from 'moment';
import { MatDialog } from '@angular/material/dialog';
import { AboutComponent } from './about/about.component';

@Component({
    selector: 'app-root',
    templateUrl: './app.component.html',
    styleUrls: []
})
export class AppComponent implements AfterViewInit {
    private weatherRef!: Observable<any[]>;
    private weatherData: any;

    dataSource: any;
    displayedColumns: string[] = ['id', 'temp', 'press', 'hum', /*'voc', 'co2'*/];

    constructor(private readonly afDatabase: AngularFireDatabase, public dialog: MatDialog) {}

    @ViewChild(MatPaginator) paginator!: MatPaginator;

    ngAfterViewInit(): void {
        this.weatherRef = this.afDatabase.list('/').snapshotChanges();

        this.weatherRef.pipe(
            map(changes =>
                changes.map(c =>
                    ({
                        key: c.payload.key,
                        data: c.payload.val(),
                    })
                )
            ),
            map(data => data.sort((a, b) =>  this.sortByDate(a, b)))
        ).subscribe(weather => {
            this.weatherData = weather;
            this.dataSource = new MatTableDataSource<any[]>(this.weatherData);
            this.dataSource.paginator = this.paginator;
        });
    }

    openDialog() {
        const dialogRef = this.dialog.open(AboutComponent);

        dialogRef.afterClosed().subscribe(result => {
          console.log(`Dialog result: ${result}`);
        });
    }

    private sortByDate(a: any, b: any) : number {
        const format = 'YYYY-MM-DD-HH-mm-ss';

        return moment.utc(b.key, format).diff(moment.utc(a.key, format));
    }
}
