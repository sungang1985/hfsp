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
            this.map = L.map(m, config).setView([lat, lng], zoom);
        },
        setGPS(g) {
            this.gps = g;
        }
    }
});