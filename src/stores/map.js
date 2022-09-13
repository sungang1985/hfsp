import { defineStore } from 'pinia'


export const useMapStore = defineStore("leaflet", {
    state: () => ({
        gps: null,
        map: null
    }),
    actions: {
        init(m) {
            let config = {
                minZoom: 7,
                maxZoom: 18,
                fullscreenControl: true,
            };
            // magnification with which the map will start
            const zoom = 18;
            // co-ordinates
            const lat = 52.22977;
            const lng = 21.01178;

            // calling map
            //this.map = L.map(m, config).setView([lat, lng], zoom);

            var osm = L.tileLayer('http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                attribution: 'Map data &copy; 2013 OpenStreetMap contributors'
            });
            this.map = L.map(m, {
                center: [0, 0],
                zoom: 2
            }).addLayer(osm);
            
        },
        setGPS(g) {
            this.gps = g;
        }
    }
});